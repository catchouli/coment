#pragma once

#include <vector>

#include "coment/SignalType.h"
#include "coment/signals/Signal.h"
#include "coment/signals/Observer.h"

namespace coment
{
    class Entity;
    class World;

    namespace impl
    {
        namespace
        {
            class World* SYSTEM_INIT_WORLD = nullptr;
        }
    }

    class SystemBase
        : public Observer
    {
    public:

        /** Create a system with a given priority. Higher priority causes
        the system to execute earlier */
        SystemBase(int priority = 0)
            : mPriority(priority), mWorld(impl::SYSTEM_INIT_WORLD) {}

        virtual ~SystemBase() {}

        /* Manager callbacks. Callbacks named on* do not have any guarantees
        as to what order they are run in. Callbacks named pre* or post* run
        before or after their associated event */

        /** Called when an entity is added to the manager */
        virtual void onEntityAdded(const Entity& e) {}

        /** Called when an entity is removed from the manager */
        virtual void onEntityRemoved(const Entity& e) {}

        /** Called before the world is updated */
        virtual void preUpdate() {}

        /** Called while the world is updated */
        virtual void onUpdate() {}

        /** Called after the world is updated */
        virtual void postUpdate() {}

        /** Get the world this system belongs to */
        World* getWorld() const;

        /** Get the priority of this system */
        int getPriority() const;

    protected:

        /** The signals that are used to emit callbacks */
        std::unordered_map<SignalType, SignalBase*>* mSignals;

    private:

        friend class World;

        /** The current world - only used during initialisation */
        static class World* INITIALISATION_WORLD;

        /** The world this system belongs to */
        World* mWorld;

        /** The execution priority of this system */
        int mPriority;

    };

    /** The basic system class, which is used by subclassing System<DerivedType>.
        Callbacks are registered on construction. */
    template <typename T>
    class System
        : public SystemBase
    {
    public:

        /** Create a system with a given priority. Higher priority causes
        the system to execute earlier */
        System(int priority = 0)
            : SystemBase(priority) {}

        virtual ~System() {}

    private:

        friend class World;

        /** Called by the world to give the manager a chance to register callbacks */
        void registerCallbacks();

    };

    /** Get the world this system belongs to */
    inline World* SystemBase::getWorld() const
    {
        return mWorld;
    }

    /** Get the priority of this system */
    inline int SystemBase::getPriority() const
    {
        return mPriority;
    }
}

#include "coment/Entity.h"

namespace coment
{
    /** Called by the world to give the manager a chance to register callbacks */
    template <typename T>
    void System<T>::registerCallbacks()
    {
        if (has_member_function_onEntityAdded<T, void, boost::mpl::vector<const Entity&>>::value)
            mSignals->at(SignalType::OnEntityAdded)->connect<const Entity&>((T*)this, &T::onEntityAdded);
        if (has_member_function_onEntityRemoved<T, void, boost::mpl::vector<const Entity&>>::value)
            mSignals->at(SignalType::OnEntityRemoved)->connect<const Entity&>((T*)this, &T::onEntityRemoved);
        if (has_member_function_preUpdate<T, void>::value)
            mSignals->at(SignalType::PreUpdate)->connect<>((T*)this, &T::preUpdate);
        if (has_member_function_onUpdate<T, void>::value)
            mSignals->at(SignalType::OnUpdate)->connect<>((T*)this, &T::onUpdate);
        if (has_member_function_postUpdate<T, void>::value)
            mSignals->at(SignalType::PostUpdate)->connect<>((T*)this, &T::postUpdate);
    }
}
