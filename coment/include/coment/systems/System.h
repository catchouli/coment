#pragma once

#include <vector>

namespace coment
{
    class Entity;

    class System
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

        /** Called while the world is updated */
        virtual void onUpdate() {}

        /** Called after the world is updated */
        virtual void postUpdate() {}

    protected:

        friend World;

        /** A pointer to the world this system belongs to */
        World* mWorld = nullptr;

    };
}