#ifndef HGL_UTIL_IMAGE_FILE_TGA_INCLUDE
#define HGL_UTIL_IMAGE_FILE_TGA_INCLUDE

#include<hgl/platform/Platform.h>
namespace hgl
{
    namespace util
    {
#pragma pack(push,1)
        struct TGAHeader
        {
            uint8 id;
            uint8 color_map_type;
            uint8 image_type;               // 1 colormap image ,2 true-color,3 grayscale

            uint16 color_map_first;
            uint16 color_map_length;
            uint8 color_map_size;

            uint16 x_origin;
            uint16 y_origin;

            uint16 width;
            uint16 height;
            uint8 bit;
            uint8 image_desc;
        };

        union TGAImageDesc
        {
            uint8 image_desc;
            struct
            {
                uint alpha_depth:4;
                uint reserved:1;
                uint direction:1;       //0 lower-left,1 upper left
            };
        };
#pragma pack(pop)

        constexpr size_t TGAHeaderSize=sizeof(TGAHeader);

        bool FillTGAHeader(TGAHeader *header,const uint16 width,const uint16 height,const uint8 channels);
    }//namespace util
}//namespace hgl
#endif//HGL_UTIL_IMAGE_FILE_TGA_INCLUDE
