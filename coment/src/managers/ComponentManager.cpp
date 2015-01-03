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
}