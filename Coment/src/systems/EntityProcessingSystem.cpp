#include "systems/EntityProcessingSystem.h"

namespace coment
{
	EntityProcessingSystem::EntityProcessingSystem()
	{

	}

	// Process unconditionally by default
	bool EntityProcessingSystem::checkProcessing()
	{
		return true;
	}

	// Automatically call process for each entity
	void EntityProcessingSystem::processEntities(const Bag<Entity>& entities)
	{
		for (unsigned int i = 0; i < entities.getSize(); ++i)
		{
			process(entities.get(i));
		}
	}
}
