#include "coment/util/EntityMap.h"

namespace coment
{
    inline EntityMap::EntityMap(dynamic_bitset<> componentTypes,
        std::shared_ptr<std::vector<Entity>> entities)
        : mComponentTypes(componentTypes), mEntities(entities)
    {

    }

    /** Get the entities in this map */
    inline std::vector<Entity>* EntityMap::getEntities()
    {
        return mEntities.get();
    }

    /** Get the entities in this map */
    inline const std::vector<Entity>* EntityMap::getEntities() const
    {
        return mEntities.get();
    }

    /** begin() proxy for range based for */
    inline std::vector<Entity>::iterator EntityMap::begin()
    {
        return mEntities->begin();
    }

    /** begin() proxy for range based for */
    inline std::vector<Entity>::iterator EntityMap::begin() const
    {
        return mEntities->begin();
    }

    /** end() proxy for range based for */
    inline std::vector<Entity>::iterator EntityMap::end()
    {
        return mEntities->end();
    }

    /** end() proxy for range based for */
    inline std::vector<Entity>::iterator EntityMap::end() const
    {
        return mEntities->end();
    }
}