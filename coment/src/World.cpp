#include "coment/World.h"

#include "coment/managers/EntityManager.h"
#include "coment/managers/ComponentManager.h"

namespace coment
{
    /** Create default managers and initialise the world */
    COMENT_API World::World()
    {
        // Create default managers
        mEntityManager = addManager<EntityManager>();
        mComponentManager = addManager<ComponentManager>();
    }
}