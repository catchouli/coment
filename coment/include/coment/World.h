#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <type_traits>

#include "coment/DLL.h"
#include "coment/managers/Manager.h"
#include "coment/systems/System.h"
#include "coment/util/TypeMap.h"

namespace coment
{
    class EntityManager;
    class ComponentManager;

    class World
    {
    public:

        /** Create default managers and initialise the world */
        COMENT_API World();

        /** Update all systems and managers */
        void COMENT_API update();

        /** Add a manager to the world, initialised with Args... */
        template <typename T, typename... Args>
        T* addManager(Args... args);

        /** Get a manager from the world */
        template <typename T>
        T* getManager() const;

        /** Remove a manager from the world */
        template <typename T>
        void removeManager() const;

        /** Add a system to the world, initialised with Args... */
        template <typename T, typename... Args>
        T* addSystem(Args... args);

        /** Get a system from the world */
        template <typename T>
        T* getSystem() const;

        /** Remove a system from the world */
        template <typename T>
        void removeSystem() const;

    private:

        /* Managers */

        /** Updates a cached manager pointer if necessary */
        template <typename T>
        void updateManagerPointer(T* ptr);

        /** Default manager pointers for fast access */
        EntityManager* mEntityManager;
        ComponentManager* mComponentManager;

        /** A map of managers */
        TypeMap<Manager> mManagerMap;

        /** A map of systems */
        TypeMap<System> mSystemMap;

    };

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