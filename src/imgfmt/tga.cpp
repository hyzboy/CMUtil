#include<hgl/util/imgfmt/tga.h>

namespace hgl
{
    namespace util
    {   
        bool FillTGAHeader(TGAHeader *header,const uint16 width,const uint16 height,const uint8 channels)
        {
            if(!header)return(false);
            if(!width||!height)return(false);

            if(channels!=1
             &&channels!=3
             &&channels!=4)return(false);

            memset(header,0,sizeof(TGAHeader));

            header->width=width;
            header->height=height;

            TGAImageDesc desc;

            desc.image_desc=0;
            
            if(channels==1)
            {
                header->image_type=3;
                header->bit=8;
            }
            else
            {
                header->image_type=2;
                header->bit=channels*8;

                if(channels==4)
                    desc.alpha_depth=8;
            }

            desc.direction=TGA_DIRECTION_UPPER_LEFT;

            header->image_desc=desc.image_desc;
            return(true);
        }
    }//namespace util
}//namespace hgl