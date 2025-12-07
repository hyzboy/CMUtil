#include<hgl/CoreType.h>
#include <cstring>
#include <vector>
#include <cstddef>

namespace hgl::crypt
{
    /**
    * 新安全接口实现。不会修改传入的 key 缓冲，内部使用本地副本。
    */
    bool OverflowEncrypt(void *target, const void *source, size_t size, const void *key, size_t key_size)
    {
        if (!target || !source || !key) return false;
        if (key_size == 0 || size == 0) return false;

        const uint8 *sp = reinterpret_cast<const uint8 *>(source);
        uint8 *tp = reinterpret_cast<uint8 *>(target);

        // 使用本地可变副本作为运行时密钥状态
        std::vector<uint8> key_state(key_size);
        memcpy(key_state.data(), key, key_size);

        size_t idx = 0; // index into key_state

        for (size_t i = 0; i < size; ++i)
        {
            uint8 k = key_state[idx];
            uint8 out = static_cast<uint8>(static_cast<unsigned>(sp[i]) + k);
            tp[i] = out;
            key_state[idx] = k ^ out;
            idx = (idx + 1) % key_size;
        }

        return true;
    }

    bool OverflowDecrypt(void *target, const void *source, size_t size, const void *key, size_t key_size)
    {
        if (!target || !source || !key) return false;
        if (key_size == 0 || size == 0) return false;

        const uint8 *sp = reinterpret_cast<const uint8 *>(source);
        uint8 *tp = reinterpret_cast<uint8 *>(target);

        std::vector<uint8> key_state(key_size);
        memcpy(key_state.data(), key, key_size);

        size_t idx = 0;

        for (size_t i = 0; i < size; ++i)
        {
            uint8 c = sp[i];
            uint8 k = key_state[idx];
            uint8 p = static_cast<uint8>(static_cast<int>(c) - static_cast<int>(k));
            tp[i] = p;
            key_state[idx] = k ^ c;
            idx = (idx + 1) % key_size;
        }

        return true;
    }
}//namespace hgl::crypt
