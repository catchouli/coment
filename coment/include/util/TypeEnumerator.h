#pragma once

#include "DLL.h"

#include <unordered_map>
#include <typeindex>

namespace coment
{
    class TypeEnumerator
    {
    public:

        /** Get whether the type is known */
        template <typename T>
        bool isTypeKnown() const;

        /** Get type ID for type */
        template <typename T>
        unsigned int getTypeId();

        /** Get current maximum ID */
        unsigned int getCurrentMax();

    private:

        unsigned int mNextTypeId;
        std::unordered_map<std::type_index, unsigned int> mTypeIndexMap;

    };
}

#include "TypeEnumerator.inl"