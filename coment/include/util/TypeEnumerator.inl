#include "TypeEnumerator.h"

namespace coment
{

    /** Get whether the type is known */
    template <typename T>
    bool TypeEnumerator::isTypeKnown() const
    {
        return (mTypeIndexMap.find(typeid(T)) != mTypeIndexMap.end());
    }

    /** Get type ID for type */
    template <typename T>
    unsigned int TypeEnumerator::getTypeId()
    {
        unsigned int id;

        // Look up id
        auto it = mTypeIndexMap.find(typeid(T));
        if (it != mTypeIndexMap.end())
        {
            // Get existing id
            id = it->second;
        }
        else
        {
            // Assign new id if missing
            id = mNextTypeId++;
            mTypeIndexMap[typeid(T)] = id;
        }

        return id;
    }

    /** Get current maximum ID */
    unsigned int TypeEnumerator::getCurrentMax()
    {
        return mNextTypeId - 1;
    }
}