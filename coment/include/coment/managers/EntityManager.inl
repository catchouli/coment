#include "coment/managers/EntityManager.h"

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
}