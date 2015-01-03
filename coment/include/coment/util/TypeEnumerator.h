#pragma once

#include "coment/DLL.h"

#include <unordered_map>
#include <typeindex>

namespace coment
{
    class TypeEnumerator
    {
    public:

        /** Initialise mNextTypeId */
        TypeEnumerator();

        /** Get whether the type is known */
        template <typename T>
        bool isTypeKnown() const;

        /** Get type ID for type */
        template <typename T>
        unsigned int getTypeId();

        /** Get current maximum ID */
        unsigned int getCurrentMax();

    private:

        /** The next available type ID (starting from 0) */
        unsigned int mNextTypeId;

        /** A map of types to type IDs */
        std::unordered_map<std::type_index, unsigned int> mTypeIndexMap;

    };
}

#include "TypeEnumerator.inl"