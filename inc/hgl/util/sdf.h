/* sdf.h — Signed Distance Field Generator
 * Pure C99, ISPC-compatible API.
 * Caller allocates all buffers. No global state. No heap allocation.
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generate a signed distance field from an 8-bit grayscale bitmap.
 *
 * Uses Felzenszwalb-Huttenlocher Exact Euclidean Distance Transform.
 * Output encoding: 128 = edge, 0..127 = inside, 129..255 = outside.
 *
 * @param width   Input image width in pixels (must be > 0).
 * @param height  Input image height in pixels (must be > 0).
 * @param spread  Maximum distance propagation radius in pixels (1..127).
 *                Controls the range of distances captured in the output.
 * @param src     Input grayscale bitmap (width*height bytes, 0=transparent, 255=opaque).
 *                src and dst MUST NOT point to the same memory.
 * @param dst     Output distance field (width*height bytes, 128=edge boundary).
 * @param temp    Scratch buffer, must be >= sdf_temp_buffer_size() bytes.
 * @return        0 on success, negative on error.
 */
int32_t sdf_generate(
    int32_t          width,
    int32_t          height,
    int32_t          spread,
    const uint8_t   *src,
    uint8_t         *dst,
    void            *temp);

/**
 * Calculate required scratch buffer size in bytes.
 */
int32_t sdf_temp_buffer_size(int32_t width, int32_t height);

#ifdef __cplusplus
}
#endif
