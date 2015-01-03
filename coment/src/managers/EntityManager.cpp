#include "coment/managers/EntityManager.h"

namespace coment
{

    /** Default constructor. Initialises members */
    COMENT_API EntityManager::EntityManager()
        : mNextAvailableUniqueId(0)
    {

    }

    /** Creates or recycles an entity */
    COMENT_API Entity EntityManager::createEntity()
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
            entityInfo.uniqueId = mNextAvailableUniqueId++;

            // Create new Entity
            entity = Entity(nextId, entityInfo.uniqueId);
        }
        else
        {
            // Recycle dead entity
            entity = mDeadEntities.back();
            mDeadEntities.pop_back();

            // Create new unique ID
            entity.mUniqueId = mNextAvailableUniqueId++;
            mEntityInfo[entity.mId].uniqueId = entity.mUniqueId;
        }

        // Callback: onEntityAdded
        for (Manager* manager : *mManagers)
        {
            manager->onEntityAdded(entity);
        }

        return entity;
    }

}