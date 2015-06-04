#include "coment/World.h"

#include "coment/Entity.h"
#include "coment/managers/EntityManager.h"
#include "coment/managers/ComponentManager.h"
#include "coment/managers/Manager.h"
#include "coment/systems/System.h"

#include <type_traits>

namespace coment
{
    template <typename T>
    void checkManagerType()
    {
        static_assert(std::is_base_of<Manager<T>, T>::value, "base class for manager T must be coment::Manager<T>");
    }

    /* Manager/System management */

    /** Add a manager to the world, initialised with args... */
    template <typename T, typename... Args>
    T* World::addManager(Args... args)
    {
        checkManagerType<T>();

        // Set global for manager initialisation
        impl::MANAGER_INIT_WORLD = this;

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
        checkManagerType<T>();

        return mManagerMap.get<T>();
    }

    /** Remove a manager from the world */
    template <typename T>
    void World::removeManager()
    {
        checkManagerType<T>();

        static_assert(!std::is_same<T, class EntityManager>::value, "Can not remove default managers");
        static_assert(!std::is_same<T, class SystemManager>::value, "Can not remove default managers");

        // Get manager ptr
        T* ptr = getManager<T>();
        
        // Remove manager from map
        mManagerMap.remove<T>();

        // Remove manager from set
        mManagerSet.erase(ptr);
    }

    template <typename T>
    void checkSystemType()
    {
        static_assert(std::is_base_of<System<T>, T>::value, "base class for system T must be coment::System<T>");
    }

    /** Add a system to the world, initialised with Args... */
    template <typename T, typename... Args>
    T* World::addSystem(Args... args)
    {
        checkSystemType<T>();

        // Set global for system initialisation
        impl::SYSTEM_INIT_WORLD = this;

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
        checkSystemType<T>();

        return mSystemMap.get<T>();
    }

    /** Remove a system from the world */
    template <typename T>
    void World::removeSystem()
    {
        checkSystemType<T>();

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
    EntityMap World::getEntityMap()
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

    /* Non-template implementations */

    /** Create default managers and initialise the world */
    inline World::World()
    {
        // Store signals in map
        mSignals[SignalType::OnEntityAdded] = &mOnEntityAdded;
        mSignals[SignalType::OnEntityRemoved] = &mOnEntityRemoved;
        mSignals[SignalType::PreUpdate] = &mPreUpdate;
        mSignals[SignalType::OnUpdate] = &mOnUpdate;
        mSignals[SignalType::PostUpdate] = &mPostUpdate;

        // Create default managers
        mEntityManager = addManager<EntityManager>(this);
        mComponentManager = addManager<ComponentManager>();
    }

    /** Update all systems and managers */
    inline void World::update()
    {
        // Preupdate signal
        mPreUpdate.emit();
        mOnUpdate.emit();
        mPostUpdate.emit();
    }

    /* Proxy API for EntityManager */

    /** Creates or recycles an entity */
    inline Entity World::createEntity()
    {
        return mEntityManager->createEntity();
    }

    /** Destroys an entity and recycles its ID */
    inline void World::destroyEntity(Entity& e)
    {
        mEntityManager->destroyEntity(e);
    }

    /** Get whether an entity is living */
    inline bool World::isLiving(Entity e) const
    {
        return mEntityManager->isLiving(e);
    }
}
