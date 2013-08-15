#include "coment/systems/EntityProcessingSystem.h"

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
	void EntityProcessingSystem::processEntities(std::vector<Entity>& entities)
	{
		for (unsigned int i = 0; i < entities.size(); ++i)
		{
			process(entities[i]);
		}
	}

	/* Events */
/*	// Indicates that this system has been registered with the world
	void EntityProcessingSystem::onRegistered()
	{

	}

	// Called before the first update of this system
	void EntityProcessingSystem::onFirstUpdate()
	{

	}

	// Called before the processing of entities begins
	void EntityProcessingSystem::onBegin()
	{

	}

	// Called after the end of processing
	void EntityProcessingSystem::onEnd()
	{

	}

	// Called when an entity is added to this system
	void EntityProcessingSystem::onAdded(const Entity& e)
	{

	}

	// Called when an entity is removed from this system
	void EntityProcessingSystem::onRemoved(const Entity& e)
	{

	}
*/}
