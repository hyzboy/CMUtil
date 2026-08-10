#include<hgl/util/hash/Hash.h>
#include<hgl/util/hash/FNV1a.h>

namespace hgl::util::hash
{
    void ComputeHash_FNV1a(const void* data, uint size, void* result)
    {
        hgl::hash::FNV1aHasher32 h;
        h.AppendBytes(data, size);

        const uint32_t digest = h;

        *reinterpret_cast<uint32_t *>(result) = digest;
    }

}//namespace hgl::util::hash
