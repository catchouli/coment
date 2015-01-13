#pragma once

#include <vector>

namespace coment
{
    class Entity;

    class System
    {
    public:

        /** Create a system with a given priority. Higher priority causes
            the system to execute earlier */
        System(int priority = 0)
            : mPriority(priority) {}

        /** Get the world this system is managed by */
        World* getWorld();

        /** Get the priority of this system */
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

        /** Called while the world is updated */
        virtual void onUpdate() {}

        /** Called after the world is updated */
        virtual void postUpdate() {}

    private:

        friend World;

        /** A pointer to the world this system is managed by */
        World* mWorld = nullptr;

        /** The execution priority of this system */
        int mPriority;

    };

    /** Get the world this system is managed by */
    inline World* System::getWorld()
    {
        return mWorld;
    }

    /** Get the priority of this system */
    inline int System::getPriority() const
    {
        return mPriority;
    }
}