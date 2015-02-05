#include "coment/managers/EntityManager.h"

#include "coment/systems/System.h"

#include <stdexcept>

namespace coment
{
    /** Get whether an entity is living */
    inline bool EntityManager::isLiving(Entity e) const
    {
        // Check the entity is initialised
        if (!e.isInitialised())
            return false;

        // Check the entity hasn't been recycled
        if (e.mUniqueId != mEntityInfo[e.mId].uniqueId)
            return false;

        // This entity definitely refers to mEntityInfo[e.mId],
        // so check that the entity is alive
        return mEntityInfo[e.mId].living;
    }

    /** Default constructor. Initialises members */
    inline EntityManager::EntityManager(World* world)
        : mNextAvailableUniqueId(0), mWorldPtr(world)
    {

    }

    /** Creates or recycles an entity */
    inline Entity EntityManager::createEntity()
    {
        Entity entity;

        // Check if there's a dead entity to recycle
        if (mDeadEntities.size() == 0)
        {
            // Create new entity
            EntityId nextId = (EntityId)mEntityInfo.size();
            mEntityInfo.resize(mEntityInfo.size() + 1);

            // Initialise new entity info
            EntityInfo entityInfo = mEntityInfo.back();

            // Create new Entity
            entity = Entity(mWorldPtr, nextId, entityInfo.uniqueId);
        }
        else
        {
            // Recycle dead entity
            entity = mDeadEntities.back();
            mDeadEntities.pop_back();
        }

        // Create new unique ID
        entity.mUniqueId = mNextAvailableUniqueId++;
        mEntityInfo[entity.mId].uniqueId = entity.mUniqueId;

        // Update entity info
        mEntityInfo[entity.mId].living = true;

        // Make entity living
        mLivingEntities.push_back(entity);

        // OnEntityAdded callback
        mSignals->at(SignalType::OnEntityAdded)->emit<const Entity&>(entity);

        return entity;
    }

    /** Destroys an entity and recycles its ID. This is delayed until the next
    update cycle, in order to prevent modification of associated containers
    while the world is updating */
    inline void EntityManager::destroyEntity(Entity& e)
    {
        // Check this entity is valid
        if (!isLiving(e))
            throw std::invalid_argument("Passed entity is uninitialised or has been destroyed");

        // Check this entity isn't already waiting for death
        auto waitingIter = std::find(mEntitiesAwaitingDeath.begin(),
            mEntitiesAwaitingDeath.end(), e);

        // TODO: make real exception types
        if (waitingIter != mEntitiesAwaitingDeath.end())
            throw std::invalid_argument("Passed entity is already queued for destruction");

        // Register entity for delayed death
        mEntitiesAwaitingDeath.push_back(e);

        // Invalidate the user's entity object
        e = Entity();
    }

    /** Handles dead entities once an update has ended */
    inline void EntityManager::postUpdate()
    {
        for (auto& ent : mEntitiesAwaitingDeath)
        {
            // Find entity in alive list
            auto it = std::find(mLivingEntities.begin(), mLivingEntities.end(), ent);

            if (it != mLivingEntities.end())
            {
                mLivingEntities.erase(it);
            }
            else
            {
                fprintf(stderr, "CRITICAL: entity waiting for death but not alive\n");
                continue;
            }

            // Add entity to dead list and invalidate unique ID
            ent.mUniqueId = -1;
            mEntityInfo[ent.mId].uniqueId = -1;
            mDeadEntities.push_back(ent);

            // Update entity info
            mEntityInfo[ent.mId].living = false;

            // OnEntityRemoved callback
            mSignals->at(SignalType::OnEntityRemoved)->emit<const Entity&>(ent);
        }

        // Clear waiting list
        mEntitiesAwaitingDeath.clear();
    }
}