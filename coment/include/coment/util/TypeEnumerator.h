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

        /** Get current maximum ID */
        unsigned int getCurrentMax();

        /* Typesafe interface */

        /** Get whether the type is known */
        template <typename T>
        bool isTypeKnown() const;

        /** Get type ID for type */
        template <typename T>
        unsigned int getTypeId();

        /* Non typesafe interface */

        /** Get whether the type is known by type_info */
        bool isTypeKnown(const std::type_info& type_info) const;

        /* Non typesafe interface by type_info */
        unsigned int getTypeId(const std::type_info& type_info);

    private:

        /** The next available type ID (starting from 0) */
        unsigned int mNextTypeId;

        /** A map of types to type IDs */
        std::unordered_map<std::type_index, unsigned int> mTypeIndexMap;

    };
}

#include "coment/util/TypeEnumerator.inl"