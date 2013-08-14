#include "coment/managers/SystemManager.h"

#include "coment/World.h"
#include "coment/utils/Functions.h"

namespace coment
{
	SystemManager::SystemManager()
	{

	}

	void SystemManager::loopStart()
	{
		// Refresh entities queued for refresh
		// Make sure to do this after updating removed entities, as entities are refreshed after$
		for (std::vector<Entity>::iterator it = _refreshed.begin(); it != _refreshed.end(); ++it)
		{
			Entity& e = *it;
			EntityInfo& entityInfo = _world->getManager<EntityManager>()->getValidEntityInfo(e);

			refreshEntity(entityInfo);
		}
 	       _refreshed.clear();
	}

	// Queue an entity to be refreshed
	void SystemManager::refresh(EntityInfo& e)
	{
		if (!e._waitingForRefresh)
		{
			e._waitingForRefresh = true;
			_refreshed.push_back((Entity)e);
		}
	}

	// Refresh an entity immediately
	void SystemManager::refreshEntity(EntityInfo& e)
	{
		// Clear waiting for refresh flag
		e._waitingForRefresh = false;

		// Update systems
		for (unsigned int i = 0; i < _systems.size(); ++i)
		{
			// If this entity's components match the system's components
			if (e.compareComponentBitmask(_systems[i]->getComponentMask()))
			{
				// If the entity isn't in the system
				if (!e.compareSystemBitmask(BitMask(1) << i))
				{
					// Add entity to system
					_systems[i]->addEntity(e);
					e._systemMask.setBit(i);
				}
			}
			// If this entity's components don't match the system's components
			else
			{
				// If the entity is in the system
				if (e.compareSystemBitmask(BitMask(1) << i))
				{
					// Remove entity from system
					_systems[i]->removeEntity(e);
					e._systemMask.clearBit(i);
				}
			}
		}
	}

	// Update all systems
	void SystemManager::update()
	{
		for (unsigned int i = 0; i < _systems.size(); ++i)
		{
			_systems[i]->update();
		}
	}
}
