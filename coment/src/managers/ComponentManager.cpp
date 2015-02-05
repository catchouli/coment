#include "coment/managers/ComponentManager.h"

namespace coment
{

    /** Update entity maps (mEntitiesByComponentBitmask) with a modified component bitmask */
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

    /* Callbacks */

    /** Update storage when an entity is added */
    void COMENT_API ComponentManager::onEntityAdded(const Entity& e)
    {
        // Add entity to array
        if (mEntityInfo.size() <= (unsigned int)e.getId())
            mEntityInfo.resize(e.getId() + 1);

        // Insert or update entity
        mEntityInfo[e.getId()].alive = true;
        mEntityInfo[e.getId()].ref = e;
        mEntityInfo[e.getId()].componentBitmask = dynamic_bitset<>();
    }

    /** Called when an entity is removed from the manager */
    void COMENT_API ComponentManager::onEntityRemoved(const Entity& e)
    {
        // Remove entity from all maps
        updateEntityMaps(e, mEntityInfo[e.getId()].componentBitmask, dynamic_bitset<>());

        // Reset entity
        mEntityInfo[e.getId()] = EntityComponentInfo();
    }

    /** Manages component map updates between updates */
    void COMENT_API ComponentManager::postUpdate()
    {
        for (auto& update : mUpdatesWaiting)
        {
            // Update mEntitiesByComponentBitmask arrays
            updateEntityMaps(std::get<0>(update), std::get<1>(update), std::get<2>(update));
        }
    }
}