#include "coment/managers/SystemManager.h"

#include "coment/utils/Functions.h"

namespace coment
{
	SystemManager::SystemManager()
	{

	}

	// Refresh an entity
	void SystemManager::refresh(EntityInfo& e)
	{
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

					// Notify system
					_systems[i]->onAdded(e);
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

					// Notify system
					_systems[i]->onRemoved(e);
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
