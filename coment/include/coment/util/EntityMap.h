#pragma once

#include "coment/util/dynamic_bitset.h"
#include "coment/util/TypeEnumerator.h"

#include <vector>
#include <memory>
#include <set>

namespace coment
{
    class Entity;

    /** An entity map class that maps entities from a bitset of component types
        to a container of entities. In reality, this is just a pointer to a
        container stored in the ComponentManager that this was obtained from,
        and not really a map */
    class EntityMap
    {
    public:

        /** Create a new entity map from a given bitset and container */
        EntityMap(dynamic_bitset<> componentTypes, std::shared_ptr<std::vector<Entity>> entities);

        /** Get the entities in this map */
        std::vector<Entity>* getEntities();

        /** Get the entities in this map */
        const std::vector<Entity>* getEntities() const;

        /** begin() proxy for range based for */
        std::vector<Entity>::iterator begin();

        /** begin() proxy for range based for */
        std::vector<Entity>::iterator begin() const;

        /** end() proxy for range based for */
        std::vector<Entity>::iterator end();

        /** end() proxy for range based for */
        std::vector<Entity>::iterator end() const;

    private:

        /** The component types that these entities include */
        dynamic_bitset<> mComponentTypes;

        /** The container of entities with these component types */
        std::shared_ptr<std::vector<Entity>> mEntities;

    };
}

#include "coment/util/EntityMap.inl"