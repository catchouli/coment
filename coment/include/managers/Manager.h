#pragma once

namespace coment
{
    class Entity;

    class Manager
    {
    public:

        /* Callbacks */
        
        /** Called when an entity is added to the manager */
        virtual void onEntityAdded(const Entity& e) {}

    };
}