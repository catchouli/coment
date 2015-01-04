#pragma once

namespace coment
{

    /** The type to use for entity IDs */
    typedef int EntityId;

    /** The entity class. Stores the ID and unique ID of an
        entity (see comments for more info) in order to indentify it.
        Also acts as a proxy interface to all entity functions in managers. */
    class Entity
    {
    public:

        /** Construct an entity with invalid (default) IDs */
        Entity();

        /** Construct an entity of given IDs */
        Entity(int id, int uniqueId);

        /** Get the ID of this entity */
        EntityId getId() const;

        /** Get the current unique ID of this entity */
        EntityId getUniqueId() const;

        /** Check if this entity has been initialised by checking its IDs */
        bool isInitialised() const;

        /** Check if two entities are the same by checking their IDs */
        bool operator==(const Entity& other);

    private:

        friend class EntityManager;

        /** The ID of this entity. Only one living entity will have this ID
             at any one time. */
        int mId;
        
        /** The unique ID of this entity. While entity IDs are recycled,
            No two entities in a given world will ever share a unique ID */
        int mUniqueId;
    };

}

#include "coment/Entity.inl"