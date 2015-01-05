#pragma once

#include <vector>

#include "coment/DLL.h"
#include "coment/Entity.h"
#include "coment/managers/Manager.h"

namespace coment
{
    class World;

    /** Meta information about an entity */
    struct EntityInfo
    {
        /** Default values */
        EntityInfo() :
            uniqueId(-1),
            living(false),
            awaitingDeath(false)
        {}

        /** The unique ID of the entity */
        int uniqueId;

        /** Whether the entity is alive */
        bool living;

        /** Whether the entity is awaiting death */
        bool awaitingDeath;
    };

    /** The manager responsible for creating and storing entities */
    class EntityManager
        : public Manager
    {
    public:

        /** Default constructor. Initialises members */
        COMENT_API EntityManager(World* world);

        /** Creates or recycles an entity */
        Entity COMENT_API createEntity();

        /** Destroys an entity and recycles its ID */
        void COMENT_API destroyEntity(Entity& e);

        /** Get whether an entity is living */
        bool isLiving(Entity e) const;

        /* Callbacks */

        /** Handles dead entities once an update has ended */
        void COMENT_API postUpdate() override;

    private:

        /** Entity current unique IDs */
        std::vector<EntityInfo> mEntityInfo;

        /** Currently living entities */
        std::vector<Entity> mLivingEntities;

        /** Currently dead entities */
        std::vector<Entity> mDeadEntities;

        /** Entities waiting to be destroyed */
        std::vector<Entity> mEntitiesAwaitingDeath;

        /** The next available unique entity ID */
        EntityId mNextAvailableUniqueId;

        /** A pointer to the world - only for passing to entities for API purposes */
        World* mWorldPtr;

    };
}

#include "coment/managers/EntityManager.inl"