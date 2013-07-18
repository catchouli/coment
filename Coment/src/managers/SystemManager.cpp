#include "coment/managers/SystemManager.h"

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
			// Check if this entity should be added.
			if (e.compareBitmask(_systems[i]->getMask()))
			{
				// Check if the entity is already in that system.
				if (!e.compareSystemBitmask(BitMask(1) << i))
				{
					_systems[i]->addEntity(e);
					e._systemMask.setBit(i);
				}
			}
			else
			{
				// Check if the entity is already in that system.
				if (!e.compareSystemBitmask(BitMask(1) << i))
				{
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
