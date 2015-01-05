#include "coment/World.h"

namespace coment
{
    /* Manager/System management */

    /** Add a manager to the world, initialised with args... */
    template <typename T, typename... Args>
    T* World::addManager(Args... args)
    {
        // Create manager
        T* ptr = mManagerMap.add<T>(args...);

        // Give vector pointer to systems/managers for callbacks
        ptr->mManagers = mManagerMap.getVector();
        ptr->mSystems = mSystemMap.getVector();

        // Update manager pointer if it's cached
        updateManagerPointer(ptr);

        // Return pointer
        return ptr;
    }

    /** Get a manager from the world */
    template <typename T>
    T* World::getManager() const
    {
        return mManagerMap.get<T>();
    }

    /** Remove a manager from the world */
    template <typename T>
    void World::removeManager() const
    {
        mManagerMap.remove<T>();
    }

    /** Add a system to the world, initialised with Args... */
    template <typename T, typename... Args>
    T* World::addSystem(Args... args)
    {
        // Create system
        T* ptr = mSystemMap.add<T>(args...);

        return ptr;
    }

    /** Get a system from the world */
    template <typename T>
    T* World::getSystem() const
    {
        return mSystemMap.get<T>();
    }

    /** Remove a system from the world */
    template <typename T>
    void World::removeSystem() const
    {
        mSystemMap.remove<T>();
    }

    /* Specilisations for default managers */

    template <>
    inline EntityManager* World::getManager() const
    {
        return mEntityManager;
    }

    template <>
    inline ComponentManager* World::getManager() const
    {
        return mComponentManager;
    }

    /* Proxy API for ComponentManager */

    /** Get an entity -> component map for a specific set of components */
    template <typename... ComponentTypes>
    EntityMap<ComponentTypes...> World::getEntityMap()
    {
        return mComponentManager->getEntityMap<ComponentTypes...>();
    }

    /** Updates a cached manager pointer if necessary
    default implementation - does nothing*/
    template <typename T>
    void World::updateManagerPointer(T* ptr)
    {
    }

    /* Specialisations */

    template <>
    inline void World::updateManagerPointer(EntityManager* ptr)
    {
        mEntityManager = ptr;
    }

    template <>
    inline void World::updateManagerPointer(ComponentManager* ptr)
    {
        mComponentManager = ptr;
    }
}