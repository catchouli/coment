#include "coment/Entity.h"

namespace coment
{
    /** Construct an entity with invalid (default) IDs */
    inline Entity::Entity()
        : mId(-1), mUniqueId(-1)
    {

    }

    /** Construct an entity of a given ID */
    inline Entity::Entity(int id, int uniqueId)
        : mId(id), mUniqueId(uniqueId)
    {

    }

    /** Get the ID of this entity */
    inline EntityId Entity::getId() const
    {
        return mId;
    }

    /** Get the current unique ID of this entity */
    inline EntityId Entity::getUniqueId() const
    {
        return mUniqueId;
    }

    /** Check if this entity has been initialised by checking its IDs */
    inline bool Entity::isInitialised() const
    {
        return (mId != -1 && mUniqueId != -1);
    }

    /** Check if two entities are the same by checking their IDs */
    inline bool Entity::operator==(const Entity& other)
    {
        return mId == other.mId && mUniqueId == other.mUniqueId;
    }
}