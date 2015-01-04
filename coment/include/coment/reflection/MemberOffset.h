#pragma once

namespace coment
{
    template <typename T, typename F>
    inline size_t dataMemberOffset(F T::* ptr)
    {
        T* typePtr = (T*)nullptr;
        F* memberPtr = &(typePtr->*ptr);

        uintptr_t offset = (uintptr_t)memberPtr - (uintptr_t)typePtr;

        return offset;
    }
}