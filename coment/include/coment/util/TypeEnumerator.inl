#include "coment/util/TypeEnumerator.h"

namespace coment
{

    /** Initialise mNextTypeId */
    inline TypeEnumerator::TypeEnumerator()
        : mNextTypeId(0)
    {

    }

    /** Get current maximum ID */
    inline unsigned int TypeEnumerator::getCurrentMax()
    {
        return mNextTypeId - 1;
    }

    /** Typesafe interface */

    /** Get whether the type is known */
    template <typename T>
    bool TypeEnumerator::isTypeKnown() const
    {
        return isTypeKnown(typeid(T));
    }

    /** Get type ID for type */
    template <typename T>
    unsigned int TypeEnumerator::getTypeId()
    {
        return getTypeId(typeid(T));
    }

    /* Non typesafe interface */

    /** Get whether the type is known by type_info */
    inline bool TypeEnumerator::isTypeKnown(const std::type_info& type_info) const
    {
        return (mTypeIndexMap.find(type_info) != mTypeIndexMap.end());
    }

    /* Non typesafe interface by type_info */
    inline unsigned int TypeEnumerator::getTypeId(const std::type_info& type_info)
    {
        unsigned int id;

        // Look up id
        auto it = mTypeIndexMap.find(type_info);
        if (it != mTypeIndexMap.end())
        {
            // Get existing id
            id = it->second;
        }
        else
        {
            // Assign new id if missing
            id = mNextTypeId++;
            mTypeIndexMap[type_info] = id;
        }

        return id;
    }
}