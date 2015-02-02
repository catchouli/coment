#include "coment/World.h"

#include "coment/Entity.h"

#include <type_traits>

namespace coment
{
    /* Manager/System management */

    /** Add a manager to the world, initialised with args... */
    template <typename T, typename... Args>
    T* World::addManager(Args... args)
    {
        // Create manager
        T* ptr = mManagerMap.add<T>(args...);

        // Add manager to set
        mManagerSet.insert(ptr);

        // Give manager pointer to signals
        ptr->mSignals = &mSignals;

        // Allow manager to register callbacks
        ptr->registerCallbacks();

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
    void World::removeManager()
    {
        const char* err = "Can not remove default managers";
        static_assert(T != EntityManager, err);
        static_assert(T != SystemManager, err);

        // Get manager ptr
        T* ptr = getManager<T>();
        
        // Remove manager from map
        mManagerMap.remove<T>();

        // Remove manager from set
        mManagerSet.erase(ptr);
    }

    /** Add a system to the world, initialised with Args... */
    template <typename T, typename... Args>
    T* World::addSystem(Args... args)
    {
        // Create system
        T* ptr = mSystemMap.add<T>(args...);

        // Add system to set
        mSystemSet.insert(ptr);

        // Give system pointer to signals
        ptr->mSignals = &mSignals;

        // Allow system to register callbacks
        ptr->registerCallbacks();

        // Give it a pointer to this world
        ptr->mWorld = this;

        // Return pointer
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
    void World::removeSystem()
    {
        // Get system ptr
        T* ptr = getSystem<T>();

        // Remove system from map
        mSystemMap.remove<T>();

        // Remove system from map
        mSystemSet.erase(ptr);
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