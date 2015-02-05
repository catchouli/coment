#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <type_traits>

#include "coment/DLL.h"
#include "coment/SignalType.h"
#include "coment/managers/Manager.h"
#include "coment/systems/System.h"
#include "coment/signals/Signal.h"
#include "coment/util/TypeMap.h"
#include "coment/util/EntityMap.h"
#include "coment/util/PriorityComparator.h"

namespace coment
{
    class EntityManager;
    class ComponentManager;

    class World
    {
    public:

        /** Create default managers and initialise the world */
        World();

        /** Update all systems and managers */
        void update();

        /* Manager management */

        /** Add a manager to the world, initialised with Args... */
        template <typename T, typename... Args>
        T* addManager(Args... args);

        /** Get a manager from the world */
        template <typename T>
        T* getManager() const;

        /** Remove a manager from the world */
        template <typename T>
        void removeManager();

        /** Add a system to the world, initialised with Args... */
        template <typename T, typename... Args>
        T* addSystem(Args... args);

        /** Get a system from the world */
        template <typename T>
        T* getSystem() const;

        /** Remove a system from the world */
        template <typename T>
        void removeSystem();

        /* Proxy API for EntityManager */

        /** Creates or recycles an entity */
        Entity createEntity();

        /** Destroys an entity and recycles its ID */
        void destroyEntity(Entity& e);

        /** Get whether an entity is living */
        bool isLiving(Entity e) const;

        /* Proxy API for ComponentManager */

        /** Get an entity -> component map for a specific set of components */
        template <typename... ComponentTypes>
        EntityMap<ComponentTypes...> getEntityMap();

    private:

        /* Managers */

        /** Updates a cached manager pointer if necessary */
        template <typename T>
        void updateManagerPointer(T* ptr);

        /** Default manager pointers for fast access */
        EntityManager* mEntityManager;
        ComponentManager* mComponentManager;

        /** A map of managers */
        TypeMap<ManagerBase> mManagerMap;
        std::multiset<ManagerBase*> mManagerSet;

        /** A map of systems */
        TypeMap<SystemBase> mSystemMap;
        std::multiset<SystemBase*> mSystemSet;

        /* Signals */

        Signal<const Entity&> mOnEntityAdded;
        Signal<const Entity&> mOnEntityRemoved;
        Signal<> mPreUpdate;
        Signal<> mOnUpdate;
        Signal<> mPostUpdate;

        std::unordered_map<SignalType, SignalBase*> mSignals;

    };
}

#include "coment/World.inl"