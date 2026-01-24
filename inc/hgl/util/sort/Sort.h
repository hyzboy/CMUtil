#pragma once

#include<hgl/type/ValueArray.h>
#include<compare>
#include<algorithm>
#include<utility>

namespace hgl
{
    /**
     * @brief 使用标准库 std::sort 进行排序（要求类型支持 operator<=> 或 operator<）
     * @tparam T 数据类型，需支持比较运算符
     * @param data 数据缓冲区指针
     * @param count 数据个数
     * @return 是否排序成功
     */
    template<typename T>
    bool Sort(T *data, int count)
    {
        if(!data || count < 2)
            return false;

        std::sort(data, data + count);
        return true;
    }

    /**
     * @brief 使用自定义比较器进行排序
     * @tparam T 数据类型
     * @tparam Compare 比较器类型（可以是函数、lambda、函数对象等）
     * @param data 数据缓冲区指针
     * @param count 数据个数
     * @param comp 比较器对象
     * @return 是否排序成功
     */
    template<typename T, typename Compare>
    bool Sort(T *data, int count, Compare comp)
    {
        if(!data || count < 2)
            return false;

        std::sort(data, data + count, comp);
        return true;
    }

    /**
     * @brief 对 ValueBuffer 进行排序（使用默认比较）
     * @tparam T 数据类型，需支持比较运算符
     * @param list ValueBuffer 引用
     * @return 是否排序成功
     */
    template<typename T>
    bool Sort(hgl::ValueBuffer<T> &list)
    {
        return Sort(list.GetData(), list.GetCount());
    }

    /**
     * @brief 对 ValueBuffer 进行排序（使用自定义比较器）
     * @tparam T 数据类型
     * @tparam Compare 比较器类型
     * @param list ValueBuffer 引用
     * @param comp 比较器对象
     * @return 是否排序成功
     */
    template<typename T, typename Compare>
    bool Sort(hgl::ValueBuffer<T> &list, Compare comp)
    {
        return Sort(list.GetData(), list.GetCount(), comp);
    }

    /**
     * @brief 堆排序实现（保留用于特殊场景，如需要稳定的内存访问模式）
     * @tparam T 数据类型
     * @tparam Compare 比较器类型，默认使用 std::less<T>
     */
    template<typename T, typename Compare = std::less<T>>
    class HeapSort
    {
    private:
        T *buffer;
        int number;
        Compare comp;

        void isift(int i, int n)
        {
            T temp = std::move(buffer[i]);
            int j = 2 * (i + 1) - 1;

            while(j <= n)
            {
                if((j < n) && comp(buffer[j], buffer[j + 1]))
                    j++;

                if(comp(temp, buffer[j]))
                {
                    buffer[i] = std::move(buffer[j]);
                    i = j;
                    j = 2 * (i + 1) - 1;
                }
                else
                {
                    j = n + 1;
                }
            }

            buffer[i] = std::move(temp);
        }

    public:
        /**
         * @brief 堆排序构造函数
         * @param buf 数据缓冲区
         * @param n 数据个数
         * @param c 比较器对象（默认使用 std::less<T>）
         */
        HeapSort(T *buf, int n, Compare c = Compare())
            : buffer(buf), number(n), comp(c)
        {
        }

        bool sort()
        {
            if(!buffer || number < 2)
                return false;

            int mm = number >> 1;

            for(int i = mm - 1; i >= 0; i--)
                isift(i, number - 1);

            for(int i = number - 1; i >= 1; i--)
            {
                std::swap(buffer[0], buffer[i]);
                isift(0, i - 1);
            }

            return true;
        }
    };

    // 兼容旧代码的示例用法说明：
    /*
    // 使用默认比较（需要类型支持 operator< 或 operator<=>）
    Sort(data_array, count);
    
    // 使用 lambda 自定义比较
    Sort(data_array, count, [](const T& a, const T& b) {
        return a.some_field < b.some_field;
    });
    
    // 使用三路比较运算符（C++20）
    Sort(data_array, count, [](const T& a, const T& b) {
        return (a <=> b) < 0;
    });
    
    // 对指针数组排序
    Sort(ptr_array, count, [](const T* a, const T* b) {
        return (*a <=> *b) < 0;
    });
    */

}//namespace hgl

