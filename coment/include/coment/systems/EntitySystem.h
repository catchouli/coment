#pragma once

#include "coment/systems/System.h"

namespace coment
{
    template <typename... ComponentTypes>
    class EntitySystem
        : public System
    {
    public:

        /** Intitialises this system with the given component types */
        EntitySystem();

    private:

        /** The entity map for this system */

    };
}

#include "coment/systems/EntitySystem.inl"