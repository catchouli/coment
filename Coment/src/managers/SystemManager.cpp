#include "managers/SystemManager.h"

namespace coment
{
	// Create a new system manager
	SystemManager::SystemManager()
	{

	}

	// Refresh an entity
	void SystemManager::refresh(EntityInfo& e) 
	{
		for (unsigned int i = 0; i < _systemMap.getSize(); ++i)
		{
			// Check if this entity should be added.
			if (e.compareBitmask(_systemMap.get(i)->getMask()))
			{
				// Check if the entity is already in that system.
				if (!e.compareSystemBitmask(BitMask(1) << i))
				{
					_systemMap.get(i)->addEntity(e);
					e._systemMask.setBit(i);
				}
			}
			else
			{
				// Check if the entity is already in that system.
				if (!e.compareSystemBitmask(BitMask(1) << i))
				{
					_systemMap.get(i)->removeEntity(e);
					e._systemMask.clearBit(i);
				}
			}
		}
	}

	// Update all the systems.
	void SystemManager::update()
	{
		for (int i = 0; i < _systemMap.getSize(); ++i) 
		{
			_systemMap.get(i)->update();
		}
	}
}
