#include "coment/managers/EntityManager.h"

#include "coment/exceptions/UninitialisedEntity.h"

namespace coment
{
	EntityManager::EntityManager()
		: _count(0), _nextEntityId(0), _nextUniqueEntityId(0), _totalCreated(0), _totalRemoved(0)
	{

	}

	EntityManager::~EntityManager()
	{

	}

	Entity EntityManager::createEntity()
	{
		Entity nextEntity;

		// If an old entity is available for reuse
		if (_dead.getSize() != 0)
		{
			// Get last dead entity to reuse
			nextEntity = _dead.popBack();
		}
		else
		{
			EntityId newId = _nextEntityId++;

			// Add entity to master list of entities if this is a completely new entity
			_entities.set(newId, EntityInfo(newId));

			// Set entity ID to return
			nextEntity._id = newId;
		}

		// Make entity alive
		_entities[nextEntity._id]._alive = true;

		// Set unique ID
		nextEntity._uniqueId = _nextUniqueEntityId++;

		// Create new entity
		_alive.add(nextEntity);

		// Update counters
		_totalCreated++;
		_count++;

		// Return entity id
		return nextEntity;
	}

	void EntityManager::removeEntity(EntityInfo& e)
	{
		// If entity is alive
		int i = _alive.contains(e);
		if (i >= 0)
		{
			// Murder entity
			e._alive = false;
			_alive.remove(i);
			_dead.add(e);

			// Reset the component and system bitmasks
			e._componentMask.clear();
			e._systemMask.clear();

			// Update counters
			_count--;
			_totalRemoved++;
		}
	}

	// Get the entity info for an entity
	EntityInfo& EntityManager::getEntityInfo(Entity e)
	{
		// If this entity is not properly initialised
		// (e.g. created by the default constructor and not the world)
		if (e.getId() == (unsigned int)-1)
		{
			// Throw an exception
			throw UninitialisedEntity();
		}

		return _entities[e.getId()];
	}
}
