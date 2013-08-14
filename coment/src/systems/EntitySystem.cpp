#include "coment/systems/EntitySystem.h"

#include <algorithm>

#include "coment/World.h"
#include "coment/utils/Functions.h"

namespace coment
{
	// Constructor
	EntitySystem::EntitySystem()
		: _world(NULL), _componentTypeManager(NULL), _enabled(true), _firstUpdate(true)
	{

	}

	// Called by the client to initiate processing
	void EntitySystem::update()
	{
		if (checkProcessing())
		{
			if (_firstUpdate)
				onFirstUpdate();

			onBegin();
			processEntities(_entities);
			onEnd();
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

	// Returns whether this system should currently process entities
	bool EntitySystem::checkProcessing()
	{
		return _enabled;
	}

	// Add an entity
	void EntitySystem::addEntity(EntityInfo& e)
	{
		// If not already in collection
		if (std::find(_entities.begin(), _entities.end(), (Entity)e) == _entities.end())
		{
			_entities.push_back(e);
			onAdded(e);
		}
	}

	// Remove an entity
	void EntitySystem::removeEntity(EntityInfo& e)
	{
		removeFirst<Entity>(_entities, e);
		onRemoved(e);
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

	// Get component type manager
	ComponentTypeManager* EntitySystem::getComponentTypeManager()
	{
		return _world->getManager<ComponentTypeManager>();
	}

	/* Events */
	// Indicates that this system has been registered with the world
	void EntitySystem::onRegistered()
	{

	}

	// Called before the first update of this system
	void EntitySystem::onFirstUpdate()
	{

	}

	// Called before the processing of entities begins
	void EntitySystem::onBegin()
	{

	}

	// Called after the end of processing
	void EntitySystem::onEnd()
	{

	}

	// Called when an entity is added to this system
	void EntitySystem::onAdded(const Entity& e)
	{

	}

	// Called when an entity is removed from this system
	void EntitySystem::onRemoved(const Entity& e)
	{

	}
}
