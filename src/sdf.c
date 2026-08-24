/* sdf.c — Signed Distance Field Generator
 * Felzenszwalb-Huttenlocher Exact Euclidean Distance Transform.
 * Pure C99, ISPC-compatible.
 */

#include "hgl/util/sdf.h"
#include <math.h>
#include <string.h>

/* Large finite value used as "infinity" for EDT.
 * Chosen so that 2*INF fits in float without overflow. */
#define SDF_INF 1e18f

/* --------------------------------------------------------------------------
 * EDT_1D — 1D squared Euclidean Distance Transform
 *
 * Felzenszwalb & Huttenlocher's lower-envelope-of-parabolas algorithm.
 *
 * f[0..n-1] : input function values (squared distances along one axis)
 * d[0..n-1] : output squared distances
 * v[0..n-1] : workspace — locations of parabolas in lower envelope
 * z[0..n]   : workspace — boundaries between parabolas
 * -------------------------------------------------------------------------- */
static void EDT_1D(const float *f, float *d, int32_t n,
                   int32_t *v, float *z)
{
    int32_t k;
    int32_t q;
    float   s;

    if (n <= 0) return;

    k    = 0;
    v[0] = 0;
    z[0] = -SDF_INF;
    z[1] =  SDF_INF;

    for (q = 1; q < n; q++) {
        for (;;) {
            /* Intersection of parabola at q with parabola at v[k].
             * Parabola at p: y = (x-p)^2 + f[p]
             * Solve: (q-p)^2 + f[q] = (x-p)^2 + f[p] for x.
             * When f[q]==f[v[k]] the parabolas have equal curvature
             * offset, so intersection is at midpoint. */
            if (f[q] == f[v[k]]) {
                s = 0.5f * ((float)q + (float)v[k]);
            } else {
                s = ((f[q] + (float)q * (float)q)
                   - (f[v[k]] + (float)v[k] * (float)v[k]))
                  / (2.0f * ((float)q - (float)v[k]));
            }

            if (s <= z[k]) {
                /* v[k] is dominated; pop it from the envelope */
                k--;
            } else {
                break;
            }
        }
        k++;
        v[k]    = q;
        z[k]    = s;
        z[k + 1] = SDF_INF;
    }

    /* Evaluate lower envelope at each integer position */
    k = 0;
    for (q = 0; q < n; q++) {
        while (z[k + 1] < (float)q) {
            k++;
        }
        {
            float diff = (float)q - (float)v[k];
            d[q] = diff * diff + f[v[k]];
        }
    }
}

/* --------------------------------------------------------------------------
 * sdf_generate — 2D SDF from grayscale bitmap
 *
 * Algorithm overview:
 *   Pass 1 (FG rows) : 1D EDT per row  for foreground mask
 *   Pass 2 (FG cols) : 1D EDT per col  → full 2D FG squared-distance
 *   Pass 3 (BG rows) : 1D EDT per row  for background mask
 *   Pass 4 (BG cols) : 1D EDT per col  → full 2D BG squared-distance
 *   Pass 5 (merge)   : combine into signed distance, encode to [0,255]
 *
 * Temp buffer layout (all regions non-overlapping):
 *   [saved_fg : wh floats]  — sqrt(fg_dist) cached between passes
 *   [rows     : wh floats]  — intermediate row-pass squared distances
 *   [cols     : wh floats]  — intermediate col-pass squared distances
 *   [work     : 4*max_dim + 1 slots] — EDT_1D scratch (f,d,v,z)
 * -------------------------------------------------------------------------- */
int32_t sdf_generate(
    int32_t         width,
    int32_t         height,
    int32_t         spread,
    const uint8_t  *src,
    uint8_t        *dst,
    void           *temp)
{
    int32_t  n;
    int32_t  max_dim;
    int32_t  wh;
    float   *base;
    float   *saved_fg;
    float   *rows_base;
    float   *cols_base;
    float   *work_base;
    int32_t  off_rows;
    int32_t  off_cols;
    int32_t  off_work;
    int32_t  i;
    int32_t  col;
    float   *f_arr;
    float   *d_arr;
    int32_t *v_arr;
    float   *z_arr;

    /* ---- Parameter validation ---- */
    if (width  <= 0)    return -1;
    if (height <= 0)    return -2;
    if (spread < 1 || spread > 127) return -3;
    if (!src || !dst || !temp)      return -4;

    n       = (width > height) ? width : height;   /* max_dim */
    max_dim = n;
    wh      = width * height;

    base = (float *)temp;

    /* Region offsets (in float units) */
    off_rows = wh;
    off_cols = off_rows + wh;
    off_work = off_cols + wh;

    saved_fg  = base;
    rows_base = base + off_rows;
    cols_base = base + off_cols;
    work_base = base + off_work;

    /* 1D EDT workspace pointers within work region.
     * Layout: f[max_dim] | d[max_dim] | v[max_dim] (int32) | z[max_dim+1]
     * int32_t and float are both 4 bytes, so offsets align cleanly. */
    f_arr = work_base;
    d_arr = work_base + max_dim;
    v_arr = (int32_t *)(work_base + 2 * max_dim);
    z_arr = work_base + 3 * max_dim;

    /* ================================================================
     * FOREGROUND PASS
     * Foreground = pixels with src[i] >= 128
     * fg_dist(p) = squared distance from p to nearest foreground pixel
     * ================================================================ */

    /* Row-wise EDT for foreground */
    for (i = 0; i < height; i++) {
        const uint8_t *row_src = src + i * width;
        int32_t j;
        for (j = 0; j < width; j++) {
            f_arr[j] = (row_src[j] >= 128) ? 0.0f : SDF_INF;
        }
        EDT_1D(f_arr, rows_base + i * width, width, v_arr, z_arr);
    }

    /* Column-wise EDT for foreground */
    for (col = 0; col < width; col++) {
        for (i = 0; i < height; i++) {
            f_arr[i] = rows_base[i * width + col];
        }
        EDT_1D(f_arr, d_arr, height, v_arr, z_arr);
        for (i = 0; i < height; i++) {
            cols_base[i * width + col] = d_arr[i];
        }
    }

    /* Cache sqrt(fg_dist) for later merge */
    for (i = 0; i < wh; i++) {
        saved_fg[i] = sqrtf(cols_base[i]);
    }

    /* ================================================================
     * BACKGROUND PASS
     * Background = pixels with src[i] < 128
     * bg_dist(p) = squared distance from p to nearest background pixel
     * ================================================================ */

    /* Row-wise EDT for background */
    for (i = 0; i < height; i++) {
        const uint8_t *row_src = src + i * width;
        int32_t j;
        for (j = 0; j < width; j++) {
            f_arr[j] = (row_src[j] < 128) ? 0.0f : SDF_INF;
        }
        EDT_1D(f_arr, rows_base + i * width, width, v_arr, z_arr);
    }

    /* Column-wise EDT for background */
    for (col = 0; col < width; col++) {
        for (i = 0; i < height; i++) {
            f_arr[i] = rows_base[i * width + col];
        }
        EDT_1D(f_arr, d_arr, height, v_arr, z_arr);
        for (i = 0; i < height; i++) {
            cols_base[i * width + col] = d_arr[i];
        }
    }

    /* ================================================================
     * MERGE PASS
     * signed_dist = sqrt(bg_dist) - sqrt(fg_dist)
     *   positive outside (closer to bg), negative inside (closer to fg)
     * Encode: dst = clamp(128 + round(signed_dist * 128 / spread), 0, 255)
     * ================================================================ */
    {
        float inv_spread = 128.0f / (float)spread;

        for (i = 0; i < wh; i++) {
            float bg_dist   = sqrtf(cols_base[i]);
            float fg_dist   = saved_fg[i];
            float signed_d  = bg_dist - fg_dist;
            float raw       = 128.0f + signed_d * inv_spread;
            int32_t val     = (int32_t)(raw + 0.5f);

            if (val < 0)   val = 0;
            if (val > 255) val = 255;

            dst[i] = (uint8_t)val;
        }
    }

    return 0;
}

/* --------------------------------------------------------------------------
 * sdf_temp_buffer_size — required scratch buffer in bytes
 *
 * Layout (float units):
 *   saved_fg : wh
 *   rows     : wh
 *   cols     : wh
 *   work     : 4 * max_dim + 1   (f, d, v-as-floats, z)
 * -------------------------------------------------------------------------- */
int32_t sdf_temp_buffer_size(int32_t width, int32_t height)
{
    int32_t max_dim;
    int32_t wh;
    int32_t work_floats;
    int32_t total_floats;

    if (width <= 0 || height <= 0) return 0;

    max_dim     = (width > height) ? width : height;
    wh          = width * height;
    work_floats = 4 * max_dim + 1;
    total_floats = 3 * wh + work_floats;

    return total_floats * (int32_t)sizeof(float);
}
