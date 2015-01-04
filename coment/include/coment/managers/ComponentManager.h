#pragma once

#include "coment/DLL.h"
#include "coment/Entity.h"
#include "coment/managers/Manager.h"
#include "coment/util/EntityMap.h"
#include "coment/util/TypeEnumerator.h"
#include "coment/util/dynamic_bitset.h"

#include <vector>

namespace coment
{
    /** Meta information about an entity in relation to its components */
    struct EntityComponentInfo
    {
        /** Default values */
        EntityComponentInfo() :
            alive(false),
            uniqueId(-1)
        {}

        /** Whether an entity has been added to this manager */
        bool alive;

        /** The unique ID of this entity */
        EntityId uniqueId;

        /** The component bitmask of this entity */
        dynamic_bitset<> componentBitmask;
    };

    /** The manager responsible for creation and storage of components */
    class ComponentManager
        : public Manager
    {
    public:

        /** Add a component to an entity */
        template <typename T, typename... Args>
        T* addComponent(Entity e, Args... args);

        /** Get a component from an entity */
        template <typename T>
        T* getComponent(Entity e);

        /** Remove a component from an entity */
        template <typename T>
        void removeComponent(Entity e);

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

        /** Check if an entity is valid */
        bool isEntityAlive(Entity e) const;

        /** A type enumerator for mapping types to ascending integer IDs */
        TypeEnumerator mTypeEnumerator;

        /** Arrays of component types tracked by this manager */
        std::vector<std::shared_ptr<void>> mComponentArrays;

        /** Component info for all entities */
        std::vector<EntityComponentInfo> mEntityInfo;

        /** Map of component bitmasks to entity arrays */
        std::unordered_map<dynamic_bitset<>, std::shared_ptr<std::vector<Entity>>> mEntitiesByComponentBitmask;

    };

    /** Add a component to an entity */
    template <typename T, typename... Args>
    T* ComponentManager::addComponent(Entity e, Args... args)
    {
        // Check if entity is valid and alive
        if (!isEntityAlive(e))
        {
            // TODO: add proper exception types
            throw 42;
        }

        // Get type ID for type
        unsigned int typeId = getComponentTypeId<T>();

        // Get component array for type
        std::vector<T>& componentArray = *getComponentArray<T>();

        // Initialise component
        componentArray[e.getId()] = T(args...);

        // Update component mask for entity
        // Get component bitmask
        dynamic_bitset<>& componentBitmask = mEntityInfo[e.getId()].componentBitmask;

        // Update component bitmask
        dynamic_bitset<> oldBitmask = componentBitmask;

        if (componentBitmask.size() <= typeId)
            componentBitmask.resize(typeId + 1);

        componentBitmask.set(typeId, true);

        // Update mEntitiesByComponentBitmask arrays
        updateEntityMaps(e, oldBitmask, componentBitmask);

        // Return a pointer to the new component
        return &componentArray[e.getId()];
    }

    /** Get a component from an entity */
    template <typename T>
    T* ComponentManager::getComponent(Entity e)
    {
        // Check if entity is valid and alive
        if (!isEntityAlive(e))
        {
            // TODO: add proper exception types
            throw 42;
        }

        // Get component array for type
        std::vector<T>& componentArray = *getComponentArray<T>();

        // Get component
        return &componentArray[e.getId()];
    }

    /** Remove a component from an entity */
    template <typename T>
    void ComponentManager::removeComponent(Entity e)
    {
        // Check if entity is valid and alive
        if (!isEntityAlive(e))
        {
            // TODO: add proper exception types
            throw 42;
        }

        // Get type id for type
        unsigned int typeId = getComponentTypeId<T>();

        // Update component mask for entity
        // Get component bitmask
        dynamic_bitset<>& componentBitmask = mEntityInfo[e.getId()].componentBitmask;

        // Update component bitmask
        dynamic_bitset<> oldBitmask = componentBitmask;
        componentBitmask.set(typeId, false);

        // Update mEntitiesByComponentBitmask arrays
        updateEntityMaps(e, oldBitmask, componentBitmask);
    }

    /* Get an entity -> component map for a specific set of components */
    template <typename... ComponentTypes>
    EntityMap<ComponentTypes...> ComponentManager::getEntityMap()
    {
        dynamic_bitset<> componentTypes = getComponentTypes<ComponentTypes...>();

        // Resize componentTypes to correct length
        componentTypes.resize(mTypeEnumerator.getCurrentMax() + 1);

        // Check for component types in map
        std::shared_ptr<std::vector<Entity>> entityArray;

        auto it = mEntitiesByComponentBitmask.find(componentTypes);
        if (it == mEntitiesByComponentBitmask.end())
        {
            // Create entity array
            entityArray = std::make_shared<std::vector<Entity>>();
            mEntitiesByComponentBitmask[componentTypes] = entityArray;

            // Populate it for the first time
            for (unsigned int i = 0; i < mEntityInfo.size(); ++i)
            {
                if (mEntityInfo[i].alive)
                {
                    dynamic_bitset<>& bitmask = mEntityInfo[i].componentBitmask;

                    // Check if this bitmask has all required components
                    if (componentTypes.is_subset_of(bitmask))
                    {
                        entityArray->push_back(Entity(i, mEntityInfo[i].uniqueId));
                    }
                }
            }
        }
        else
        {
            entityArray = it->second;
        }

        return EntityMap<ComponentTypes...>(componentTypes, entityArray);
    }

    /** Get a type ID for a specific component type */
    template <typename T>
    unsigned int ComponentManager::getComponentTypeId()
    {
        // Get type id
        unsigned int id = mTypeEnumerator.getTypeId<T>();

        return id;
    }

    /** Get an array for a specific component type */
    template <typename T>
    std::vector<T>* ComponentManager::getComponentArray()
    {
        // Get type id
        unsigned int id = getComponentTypeId<T>();

        // Create array if not existent
        // Check if arrays array long enough
        if (mComponentArrays.size() <= id)
        {
            // Resize arrays array to accomodate this type
            mComponentArrays.resize(id + 1);
        }

        // Check if this type has an array
        if (mComponentArrays[id] == nullptr)
        {
            // Create this type's array
            mComponentArrays[id] = std::make_shared<std::vector<T>>();
        }

        // Return component array
        std::vector<T>* arr = static_cast<std::vector<T>*>(mComponentArrays[id].get());

        // Resize to number of entities if smaller
        if (arr->size() < mEntityInfo.size())
            arr->resize(mEntityInfo.size());

        return arr;
    }

    /** Decompose a variadic type pack into a list of integer ids */
    template <typename T1>
    dynamic_bitset<> ComponentManager::getComponentTypes()
    {
        // Create new (0) bitset
        dynamic_bitset<> componentTypes;

        // Get this type's id
        unsigned int id = mTypeEnumerator.getTypeId<T1>();

        // Ensure bitset is long enough for type
        if (componentTypes.size() <= id)
            componentTypes.resize(id + 1);

        // Set type's bit to true
        componentTypes.set(id, true);

        return componentTypes;
    }

    /** Decompose a variadic type pack into a list of integer ids */
    template <typename T1, typename T2, typename... ComponentTypes>
    dynamic_bitset<> ComponentManager::getComponentTypes()
    {
        // Create new (0) bitset
        dynamic_bitset<> componentTypes;

        // resize a to be at least as long as b, and then a |= b
        auto combine = [](dynamic_bitset<>& a, dynamic_bitset<>& b)
        {
            if (a.size() < b.size())
                a.resize(b.size());

            a |= b;
        };

        // Get bit for T1 and add it to componentTypes bitmask
        combine(componentTypes, getComponentTypes<T1>());

        // Get bits for the rest and add them to componentTypes bitmask
        combine(componentTypes, getComponentTypes<T2, ComponentTypes...>());

        return componentTypes;
    }

    /** Check if an entity is valid */
    inline bool ComponentManager::isEntityAlive(Entity e) const
    {
        // Check the entity is initialised
        if (!e.isInitialised())
            return false;

        // Check the entity hasn't been recycled
        if (e.getUniqueId() != mEntityInfo[e.getId()].uniqueId)
            return false;

        // This entity definitely refers to mEntityInfo[e.mId],
        // so check that the entity is alive
        return mEntityInfo[e.getId()].alive;
    }
}