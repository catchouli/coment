#include "coment/util/EntityMap.h"

namespace coment
{
    template <typename... ComponentTypes>
    EntityMap<ComponentTypes...>::EntityMap(dynamic_bitset<> componentTypes,
        std::shared_ptr<std::vector<Entity>> entities)
        : mComponentTypes(componentTypes), mEntities(entities)
    {

    }

    /** Get the entities in this map */
    template <typename... ComponentTypes>
    std::vector<Entity>* EntityMap<ComponentTypes...>::getEntities()
    {
        return mEntities.get();
    }

    /** Get the entities in this map */
    template <typename... ComponentTypes>
    const std::vector<Entity>* EntityMap<ComponentTypes...>::getEntities() const
    {
        return mEntities.get();
    }

    /** begin() proxy for range based for */
    template <typename... ComponentTypes>
    std::vector<Entity>::iterator EntityMap<ComponentTypes...>::begin()
    {
        return mEntities->begin();
    }

    /** begin() proxy for range based for */
    template <typename... ComponentTypes>
    std::vector<Entity>::iterator EntityMap<ComponentTypes...>::begin() const
    {
        return mEntities->begin();
    }

    /** end() proxy for range based for */
    template <typename... ComponentTypes>
    std::vector<Entity>::iterator EntityMap<ComponentTypes...>::end()
    {
        return mEntities->end();
    }

    /** end() proxy for range based for */
    template <typename... ComponentTypes>
    std::vector<Entity>::iterator EntityMap<ComponentTypes...>::end() const
    {
        return mEntities->end();
    }
}