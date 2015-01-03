#pragma once

#include "DLL.h"

#include <vector>
#include "Manager.h"
#include "../Entity.h"

namespace coment
{
    /** Meta information about an entity */
    struct EntityInfo
    {
        int uniqueId;
    };

    /** The manager responsible for creating and storing entities */
    class EntityManager
        : public Manager
    {
    public:

        /** Default constructor. Initialises members */
        COMENT_API EntityManager();

        /** Creates or recycles an entity */
        COMENT_API Entity createEntity();

    private:

        /** Entity current unique IDs */
        std::vector<EntityInfo> mEntityInfo;

        /** Currently living entities */
        std::vector<Entity> mLivingEntities;

        /** Currently dead entities */
        std::vector<Entity> mDeadEntities;

        /** The next available unique entity ID */
        EntityId mNextAvailableUniqueId;

    };
}