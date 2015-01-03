#pragma once

#include "DLL.h"

#include <vector>
#include "Manager.h"
#include "../Entity.h"
#include "../util/EntityMap.h"
#include "../util/TypeEnumerator.h"
#include "../util/dynamic_bitset.h"

namespace coment
{
    /** The manager responsible for creation and storage of components */
    class ComponentManager
        : public Manager
    {
    public:

        /** Add a component to an entity */
        template <typename T, typename... Args>
        void addComponent(Entity e, Args... args);

        /** Remove a component from an entity */
        template <typename T>
        void removeComponent(Entity e);

        /** Get an entity -> component map for a specific set of components */
        template <typename... ComponentTypes>
        EntityMap<ComponentTypes...> getEntityMap();

        /* Callbacks */

        /** Called when an entity is added to the manager */
        void onEntityAdded(const Entity& e) override
        {
            // TODO: move this into a source file (not done for now so we don't have to export it..)
            // Add entity to array
            if (mEntityArray.size() <= (unsigned int)e.getId())
                mEntityArray.resize(e.getId() + 1);

            // Insert or update entity
            mEntityArray[e.getId()] = e;

            // Reserve bitmasks for entity
            unsigned int bitmaskCount = mComponentBitmasks.size();

            if (bitmaskCount <= (unsigned int)e.getId())
            {
                // Create bitmasks for new entities
                mComponentBitmasks.resize(e.getId() + 1);

                // Make the new ones the right size
                for (unsigned int i = bitmaskCount; i < mComponentBitmasks.size(); ++i)
                {
                    // The current number of registered types = mTypeEnumerator.getCurrentMax() + 1
                    mComponentBitmasks[i].resize(mTypeEnumerator.getCurrentMax() + 1);
                }
            }
        }

    private:

        // Update entity maps (mEntitiesByComponentBitmask) with a modified component bitmask
        void updateEntityMaps(Entity e, const dynamic_bitset<>& oldBitmask,
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

        /** A type enumerator for mapping types to ascending integer IDs */
        TypeEnumerator mTypeEnumerator;

        /** Arrays of component types tracked by this manager */
        std::vector<std::shared_ptr<void>> mComponentArrays;

        /** Component bitmasks for all entities */
        std::vector<dynamic_bitset<>> mComponentBitmasks;

        /** Entity array for all entities, dead or alive */
        std::vector<Entity> mEntityArray;

        /** Map of component bitmasks to entity arrays */
        std::unordered_map<dynamic_bitset<>, std::shared_ptr<std::vector<Entity>>> mEntitiesByComponentBitmask;

    };

    /** Add a component to an entity */
    template <typename T, typename... Args>
    void ComponentManager::addComponent(Entity e, Args... args)
    {
        // Get type ID for type
        unsigned int typeId = getComponentTypeId<T>();

        // Get component array for type
        std::vector<T>& componentArray = *getComponentArray<T>();

        // Initialise component
        componentArray[e.getId()] = T(args...);

        // Update component mask for entity
        // Get component bitmask
        dynamic_bitset<>& componentBitmask = mComponentBitmasks[e.getId()];

        // Update component bitmask
        dynamic_bitset<> oldBitmask = componentBitmask;
        componentBitmask.set(typeId, true);

        // Update mEntitiesByComponentBitmask arrays
        updateEntityMaps(e, oldBitmask, componentBitmask);
    }

    /** Remove a component from an entity */
    template <typename T>
    void ComponentManager::removeComponent(Entity e)
    {
        // Get type id for type
        unsigned int typeId = getComponentTypeId<T>();

        // Update component mask for entity
        // Get component bitmask
        dynamic_bitset<>& componentBitmask = mComponentBitmasks[e.getId()];

        // Update component bitmask
        dynamic_bitset<> oldBitmask = componentBitmask;
        componentBitmask.set(typeId, false);

        // Update mEntitiesByComponentBitmask arrays
        updateEntityMaps(e, oldBitmask, componentBitmask);
    }

    void ComponentManager::updateEntityMaps(Entity e,
        const dynamic_bitset<>& oldBitmask, const dynamic_bitset<>& newBitmask)
    {
        // Update entities by component sets
        for (auto& pair : mEntitiesByComponentBitmask)
        {
            auto& bitmask = pair.first;
            auto& arr = pair.second;

            bool inCollection = bitmask.is_subset_of(oldBitmask);
            bool shouldBeInCollection = bitmask.is_subset_of(newBitmask);

            // If we need to add it
            if (!inCollection && shouldBeInCollection)
            {
                arr->push_back(e);
            }
            // If we need to remove it
            else if (inCollection && !shouldBeInCollection)
            {
                auto it = std::remove_if(arr->begin(), arr->end(),
                    [&e](const Entity& innerEntity)
                {
                    if (e.getId() == innerEntity.getId())
                        return true;
                    else
                        return false;
                });

                arr->erase(it, arr->end());
            }
        }
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
            for (int i = 0; i < (int)mComponentBitmasks.size(); ++i)
            {
                dynamic_bitset<>& bitmask = mComponentBitmasks[i];

                // Check if this bitmask has all required components
                if (componentTypes.is_subset_of(bitmask))
                {
                    entityArray->push_back(mEntityArray[i]);
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
        bool newType = !mTypeEnumerator.isTypeKnown<T>();

        // Get type id
        unsigned int id = mTypeEnumerator.getTypeId<T>();

        // Resize arrays if this is a new type
        if (newType)
        {
            for (auto& bitmask : mComponentBitmasks)
            {
                // known type count = mTypeEnumerator.getCurrentMax() + 1
                bitmask.resize(mTypeEnumerator.getCurrentMax() + 1);
            }

            // Update map with new length bitmasks
            std::unordered_map<dynamic_bitset<>, std::shared_ptr<std::vector<Entity>>> newEntityMap;

            for (auto& pair : mEntitiesByComponentBitmask)
            {
                // known type count = mTypeEnumerator.getCurrentMax() + 1
                dynamic_bitset<> newBitmask = pair.first;
                newBitmask.resize(mTypeEnumerator.getCurrentMax() + 1);
                newEntityMap[newBitmask] = pair.second;
            }

            // Replace old map
            mEntitiesByComponentBitmask = newEntityMap;
        }

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
        if (arr->size() < mComponentBitmasks.size())
            arr->resize(mComponentBitmasks.size());

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
}