#include "coment/managers/Manager.h"
#include "coment/systems/System.h"

namespace coment
{
    /** Get the priority of this manager */
    inline int Manager::getPriority() const
    {
        return mPriority;
    }

    struct SystemPtrComparator
    {
        bool operator()(const System* lhs, const System* rhs)
        {
            return lhs->getPriority() > rhs->getPriority();
        }
    };

    struct ManagerPtrComparator
    {
        bool operator()(const Manager* lhs, const Manager* rhs)
        {
            return lhs->getPriority() > rhs->getPriority();
        }
    };
}