#include "coment/Entity.h"

#include "coment/managers/ComponentManager.h"

namespace coment
{
    /** Construct an entity with invalid (default) IDs */
    inline Entity::Entity(World* world)
        : mWorldPtr(world), mId(-1), mUniqueId(-1)
    {

    }

    /** Construct an entity of a given ID */
    inline Entity::Entity(World* world, int id, int uniqueId)
        : mWorldPtr(world), mId(id), mUniqueId(uniqueId)
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

    /* ComponentManager proxy API */

    /** Add a component to an entity */
    template <typename T, typename... Args>
    T* Entity::addComponent(Args... args)
    {
        if (!isInitialised())
            throw std::invalid_argument("addComponent called on uninitialised or dead entity");

        // World::getManager is specialised for default managers to prevent a dictionary lookup
        return mWorldPtr->getManager<ComponentManager>()->addComponent<T>(*this, args...);
    }

    /** Get a component from an entity */
    template <typename T>
    T* Entity::getComponent()
    {
        if (!isInitialised())
            throw std::invalid_argument("getComponent called on uninitialised or dead entity");

        // World::getManager is specialised for default managers to prevent a dictionary lookup
        return mWorldPtr->getManager<ComponentManager>()->getComponent<T>(*this);
    }

    /** Remove a component from an entity */
    template <typename T>
    void Entity::removeComponent()
    {
        if (!isInitialised())
            throw std::invalid_argument("removeComponent called on uninitialised or dead entity");

        // World::getManager is specialised for default managers to prevent a dictionary lookup
        return mWorldPtr->getManager<ComponentManager>()->removeComponent<T>(*this);
    }
}