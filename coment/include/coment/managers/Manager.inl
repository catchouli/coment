#include "coment/Entity.h"
#include "coment/managers/Manager.h"
#include "coment/systems/System.h"

namespace coment
{
    /** Called by the world to give the manager a chance to register callbacks */
    template <typename T>
    void Manager<T>::registerCallbacks()
    {
        if (has_member_function_onEntityAdded<T, void, boost::mpl::vector<const Entity&>>::value)
            mSignals->at(SignalType::OnEntityAdded)->connect<const Entity&>((T*)this, &T::onEntityAdded);
        if (has_member_function_onEntityRemoved<T, void, boost::mpl::vector<const Entity&>>::value)
            mSignals->at(SignalType::OnEntityRemoved)->connect<const Entity&>((T*)this, &T::onEntityRemoved);
        if (has_member_function_preUpdate<T, void>::value)
            mSignals->at(SignalType::PreUpdate)->connect<>((T*)this, &T::preUpdate);
        if (has_member_function_postUpdate<T, void>::value)
            mSignals->at(SignalType::PostUpdate)->connect<>((T*)this, &T::postUpdate);
    }

    /** Get the world this system belongs to */
    inline World* ManagerBase::getWorld() const
    {
        return mWorld;
    }

    /** Get the priority of this manager */
    inline int ManagerBase::getPriority() const
    {
        return mPriority;
    }

    struct SystemPtrComparator
    {
        bool operator()(const SystemBase* lhs, const SystemBase* rhs)
        {
            return lhs->getPriority() > rhs->getPriority();
        }
    };

    struct ManagerPtrComparator
    {
        bool operator()(const ManagerBase* lhs, const ManagerBase* rhs)
        {
            return lhs->getPriority() > rhs->getPriority();
        }
    };
}