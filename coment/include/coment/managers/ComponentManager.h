#pragma once

#include "coment/DLL.h"
#include "coment/Entity.h"
#include "coment/managers/Manager.h"
#include "coment/util/EntityMap.h"
#include "coment/util/TypeEnumerator.h"
#include "coment/util/dynamic_bitset.h"

#include <vector>
#include <stdexcept>

namespace coment
{
    class Entity;

    /** Meta information about an entity in relation to its components */
    struct EntityComponentInfo;

    /** The manager responsible for creation and storage of components */
    class ComponentManager
        : public Manager<ComponentManager>
    {
    public:

        /* Template API */

        /** Add a component to an entity */
        template <typename T, typename... Args>
        T* addComponent(const Entity& e, Args... args);

        /** Get a component from an entity */
        template <typename T>
        T* getComponent(const Entity& e);

        /** Remove a component from an entity */
        template <typename T>
        void removeComponent(const Entity& e);

        /** Get an entity -> component map for a specific set of components */
        template <typename... ComponentTypes>
        EntityMap<ComponentTypes...> getEntityMap();

        /* Callbacks */

        /** Called when an entity is added to the manager */
        void COMENT_API onEntityAdded(const Entity& e) override;

        /** Called when an entity is removed from the manager */
        void COMENT_API onEntityRemoved(const Entity& e) override;

    private:

        /** Update entity maps (mEntitiesByComponentBitmask) with a modified component bitmask */
        void COMENT_API updateEntityMaps(Entity e, const dynamic_bitset<>& oldBitmask,
            const dynamic_bitset<>& newBitmask);

        /** Get a type ID for a specific component type */
        template <typename T>
        unsigned int getComponentTypeId();

        /** Get an array for a specific component type */
        template <typename T>
        std::vector<T>* getComponentArray();

        /** Decompose a variadic type pack into a list of integer ids */
        template <typename T1>
        dynamic_bitset<> getComponentTypes();

        /** Decompose a variadic type pack into a list of integer ids */
        template <typename T1, typename T2, typename... ComponentTypes>
        dynamic_bitset<> getComponentTypes();

        /** Get if an entity is valid */
        bool isEntityAlive(const Entity& e) const;

        /** Check if an entity is valid and throw an exception otherwise */
        void checkEntityAlive(const Entity& e) const;

        /** A type enumerator for mapping types to ascending integer IDs */
        TypeEnumerator mTypeEnumerator;

        /** Arrays of component types tracked by this manager */
        std::vector<std::shared_ptr<void>> mComponentArrays;

        /** Component info for all entities */
        std::vector<EntityComponentInfo> mEntityInfo;

        /** Map of component bitmasks to entity arrays */
        std::unordered_map<dynamic_bitset<>,
            std::shared_ptr<std::vector<Entity>>> mEntitiesByComponentBitmask;

    };
}

#include "coment/managers/ComponentManager.inl"