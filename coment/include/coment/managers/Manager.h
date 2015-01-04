#pragma once

#include <vector>

namespace coment
{
    class Entity;
    class System;

    class Manager
    {
    public:

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

        /** All managers known by this manager's world */
        const std::vector<Manager*>* mManagers;

        /** All systems known by this manager's world */
        const std::vector<System*>* mSystems;

    };
}