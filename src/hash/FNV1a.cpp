#include<hgl/util/hash/Hash.h>
#include<hgl/type/FNV1a.h>

namespace hgl::util::hash
{
    void ComputeHash_FNV1a(const void* data, uint size, void* result)
    {
        const uint32_t digest = hgl::hash::FNV1aAppendBytes(hgl::hash::FNV1aInit<uint32_t>(), data, size);

        *reinterpret_cast<uint32_t *>(result) = digest;
    }

}//namespace hgl::util::hash
