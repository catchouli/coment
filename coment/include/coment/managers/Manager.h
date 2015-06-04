#pragma once

#include <vector>
#include <set>

#include "coment/SignalType.h"
#include "coment/signals/Signal.h"
#include "coment/signals/Observer.h"
#include "coment/util/PriorityComparator.h"

namespace coment
{
    class Entity;
    class SystemBase;

    namespace impl
    {
        namespace
        {
            class World* MANAGER_INIT_WORLD = nullptr;
        }
    }

    class ManagerBase
        : public Observer
    {
    public:

        /** Allows the derived class to specify a priority for updates to the manager.
            A higher priority means that this manager will be processed first */
        ManagerBase(int priority = 0)
            : mPriority(priority), mWorld(impl::MANAGER_INIT_WORLD) {}

        ~ManagerBase() {}

        /** Get the world this system belongs to */
        World* getWorld() const;

        /** Get the priority of this manager */
        int getPriority() const;

        /* Manager callbacks. Callbacks named on* do not have any guarantees
           as to what order they are run in. Callbacks named pre* or post* run
           before or after their associated event */
        
        /** Called when an entity is added to the manager */
        virtual void onEntityAdded(const Entity& e) {}

        /** Called when an entity is removed from the manager */
        virtual void onEntityRemoved(const Entity& e) {}

        /** Called before the world is updated */
        virtual void preUpdate() {}

        /** Called after the world is updated */
        virtual void postUpdate() {}

    protected:

        /** The signals that are used to emit callbacks */
        std::unordered_map<SignalType, SignalBase*>* mSignals;

    private:

        friend class World;

        /** The world this manager belongs to */
        class World* mWorld;

        /** The priority of updates to this manager */
        int mPriority;

    };

    template <typename T>
    class Manager
        : public ManagerBase
    {
    public:

        /** Allows the derived class to specify a priority for updates to the manager.
        A higher priority means that this manager will be processed first */
        Manager(int priority = 0)
            : ManagerBase(priority) {}

        ~Manager() {}

    private:

        friend class World;

        /** Called by the world to give the manager a chance to register callbacks */
        void registerCallbacks();

    };
}

#include "coment/managers/Manager.inl"
