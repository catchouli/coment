#include "systems/EntityProcessingSystem.h"

namespace coment
{
	EntityProcessingSystem::EntityProcessingSystem()
	{

	}

	// Process only if the system is enabled by default
	bool EntityProcessingSystem::checkProcessing()
	{
		return getEnabled();
	}

	// Automatically call process for each entity
	void EntityProcessingSystem::processEntities(Bag<Entity>& entities)
	{
		for (unsigned int i = 0; i < entities.getSize(); ++i)
		{
			process(entities.get(i));
		}
	}
}
