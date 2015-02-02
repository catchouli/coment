#include "coment/World.h"

#include "coment/managers/EntityManager.h"
#include "coment/managers/ComponentManager.h"

namespace coment
{
    /** Create default managers and initialise the world */
    COMENT_API World::World()
    {
        // Store signals in map
        mSignals[SignalType::OnEntityAdded] = &mOnEntityAdded;
        mSignals[SignalType::OnEntityRemoved] = &mOnEntityRemoved;
        mSignals[SignalType::PreUpdate] = &mPreUpdate;
        mSignals[SignalType::OnUpdate] = &mOnUpdate;
        mSignals[SignalType::PostUpdate] = &mPostUpdate;

        // Create default managers
        mEntityManager = addManager<EntityManager>(this);
        mComponentManager = addManager<ComponentManager>();
    }

    /** Update all systems and managers */
    void COMENT_API World::update()
    {
        // Preupdate signal
        mPreUpdate.emit();
        mOnUpdate.emit();
        mPostUpdate.emit();
    }

    /* Proxy API for EntityManager */

    /** Creates or recycles an entity */
    Entity COMENT_API World::createEntity()
    {
        return mEntityManager->createEntity();
    }

    /** Destroys an entity and recycles its ID */
    void COMENT_API World::destroyEntity(Entity& e)
    {
        mEntityManager->destroyEntity(e);
    }

    /** Get whether an entity is living */
    bool World::isLiving(Entity e) const
    {
        return mEntityManager->isLiving(e);
    }
}