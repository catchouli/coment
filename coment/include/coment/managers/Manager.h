#pragma once

#include <vector>

namespace coment
{
    class Entity;

    class Manager
    {
    public:

        /* Callbacks */
        
        /** Called when an entity is added to the manager */
        virtual void onEntityAdded(const Entity& e) {}

    protected:

        friend class World;

        /** All managers known by this manager's world */
        std::vector<Manager*>* mManagers;
    };
}