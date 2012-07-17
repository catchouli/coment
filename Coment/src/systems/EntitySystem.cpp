#include "systems/EntitySystem.h"

namespace coment
{
	// Called by the client to initiate processing
	void EntitySystem::update()
	{
		if (checkProcessing())
		{
			begin();
			processEntities(_entities);
			end();
		}
	}

	// Called during initialisation of this system
	void EntitySystem::initialise()
	{

	}

	// Called before the processing of entities begins
	void EntitySystem::begin()
	{

	}

	// Called after the end of processing
	void EntitySystem::end()
	{

	}

	// Returns whether this system should currently process entities
	bool EntitySystem::checkProcessing()
	{
		// Return true by default (this can be overridden)
		return true;
	}

	// Called when an entity is added to this system
	void EntitySystem::added(Entity e)
	{

	}

	// Called when an entity is removed from this system
	void EntitySystem::removed(Entity e)
	{

	}

	// Constructor
	EntitySystem::EntitySystem()
	{

	}

	// Add an entity
	void EntitySystem::addEntity(EntityInfo& e)
	{
		_entities.add(e);
	}
		
	// Remove an entity
	void EntitySystem::removeEntity(EntityInfo& e)
	{
		int index = _entities.getIndex(e);
		if (index > 0)
			_entities.remove(index);
	}

	// Set the world
	void EntitySystem::setWorld(World* world)
	{
		_world = world;
	}

	// Get the bitmask
	BitMask EntitySystem::getMask()
	{
		return _bitmask;
	}
}
