#pragma once

#include <vector>

#include "coment/DLL.h"
#include "coment/Entity.h"
#include "coment/managers/Manager.h"

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
        Entity COMENT_API createEntity();

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