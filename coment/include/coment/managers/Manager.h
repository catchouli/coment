#pragma once

#include <vector>
#include <set>

#include "coment/util/PriorityComparator.h"

namespace coment
{
    class Entity;
    class System;

    class Manager
    {
    public:

        /** Allows the derived class to specify a priority for updates to the manager.
            A higher priority means that this manager will be processed first */
        Manager(int priority = 0)
            : mPriority(priority) {}

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

        friend class World;

        /** The priority of updates to this manager */
        int mPriority;

        /** All managers known by this manager's world */
        const std::multiset<Manager*, PriorityComparator<Manager>>* mManagers;

        /** All systems known by this manager's world */
        const std::multiset<System*, PriorityComparator<System>>* mSystems;

    };
}

#include "coment/managers/Manager.inl"