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

    /** Update all systems and managers */
    void COMENT_API World::update()
    {
        // Manager Callback: preUpdate
        // Notify managers that an update is about to occur
        for (auto& mgr : mManagerPointerVec)
        {
            mgr->preUpdate();
        }

        // Manager Callback: postUpdate
        // Notify managers that an update has just occurred
        for (auto& mgr : mManagerPointerVec)
        {
            mgr->postUpdate();
        }
    }
}