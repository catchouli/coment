#include "coment/systems/EntitySystem.h"

#include <algorithm>

#include "coment/World.h"
#include "coment/utils/Functions.h"

namespace coment
{
	// Constructor
	EntitySystem::EntitySystem()
		: _world(NULL), _componentTypeManager(NULL), _enabled(true)
	{

	}

	// Indicates that this system has been registered with the world
	void EntitySystem::onRegistered()
	{

	}

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

	// Enable processing of this system
	void EntitySystem::setEnabled(bool enabled)
	{
		_enabled = enabled;
	}

	// Get whether this system is enabled
	bool EntitySystem::getEnabled()
	{
		return _enabled;
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
		return _enabled;
	}

	// Called when an entity is added to this system
	void EntitySystem::added(const Entity& e)
	{

	}

	// Called when an entity is removed from this system
	void EntitySystem::removed(const Entity& e)
	{

	}

	// Add an entity
	void EntitySystem::addEntity(EntityInfo& e)
	{
		// If not already in collection
		if (std::find(_entities.begin(), _entities.end(), (Entity)e) == _entities.end())
			_entities.push_back(e);
	}

	// Remove an entity
	void EntitySystem::removeEntity(EntityInfo& e)
	{
		removeFirst(_entities, (Entity)e);
	}

	// Set the world
	void EntitySystem::setWorld(World* world)
	{
		_world = world;
	}

	// Get the bitmask
	BitMask EntitySystem::getComponentMask()
	{
		return _bitmask;
	}

	ComponentTypeManager* EntitySystem::getComponentTypeManager()
	{
		return _world->getManager<ComponentTypeManager>();
	}
}
