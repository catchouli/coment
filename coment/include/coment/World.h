#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <type_traits>
#include <cassert>

#include "coment/DLL.h"
#include "coment/managers/Manager.h"

namespace coment
{
    class EntityManager;
    class ComponentManager;

    class World
    {
    public:

        /** Create default managers and initialise the world */
        COMENT_API World();

        /** Add a manager to the world, initialised with Args... */
        template <typename T, typename... Args>
        T* addManager(Args... args);

        /** Get a manager from the world */
        template <typename T>
        T* getManager() const;

    private:

        /** Add a manager to the world, initialised with Args... */
        template <typename... Args>
        EntityManager* addManager(Args... args);

        /* Managers */

        /** Default manager pointers for fast access */
        EntityManager* mEntityManager;
        ComponentManager* mComponentManager;

        /** All managers by type */
        std::unordered_map<std::type_index, std::shared_ptr<Manager>> mManagers;

        /** All managers */
        std::vector<Manager*> mManagerPointerVec;

    };

    template <typename T, typename... Args>
    T* World::addManager(Args... args)
    {
        static_assert(std::is_base_of<Manager, T>::value,
            "Template parameter T to addManager() must be a derived class of Manager");

        // Create manager
        std::shared_ptr<T> mgr = std::make_shared<T>(args...);

        // If this type already has a manager registered, remove it
        auto mapIt = mManagers.find(typeid(T));
        if (mapIt != mManagers.end())
        {
            // Remove from map
            std::shared_ptr<Manager> oldmgr = mapIt->second;
            mManagers.erase(mapIt);
            
            // Remove from vector
            auto begin = mManagerPointerVec.begin();
            auto end = mManagerPointerVec.end();
            auto vecIt = std::find(begin, end, oldmgr.get());

            // The vector should definitely contain this manager if it was in the map
            assert(vecIt != mManagerPointerVec.end());
            mManagerPointerVec.erase(vecIt);
        }

        // Store manager in map
        mManagers[typeid(T)] = mgr;

        // Store manager in vector
        mManagerPointerVec.push_back(mgr.get());

        // Give manager a pointer to the other managers for callbacks
        mgr->mManagers = &mManagerPointerVec;

        // Return manager pointer
        return mgr.get();
    }

    template <typename T>
    T* World::getManager() const
    {
        return static_cast<T*>(mManagers.at(typeid(T)).get());
    }

    template <>
    EntityManager* World::getManager() const
    {
        return mEntityManager;
    }

    template <>
    ComponentManager* World::getManager() const
    {
        return mComponentManager;
    }
}