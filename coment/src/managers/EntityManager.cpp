#include "coment/managers/EntityManager.h"

#include <stdlib.h>
#include <stdio.h>

#include "coment/World.h"
#include "coment/exceptions/DeadEntity.h"
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

	void EntityManager::loopStart()
	{
		// Remove entities queued for removal
		for (std::vector<Entity>::iterator it = _removed.begin(); it != _removed.end(); ++it)
		{
			Entity& e = *it;
			EntityInfo& entityInfo = getValidEntityInfo(e);

			removeEntity(entityInfo);
		}
		_removed.clear();
	}

	Entity EntityManager::createEntity()
	{
		Entity nextEntity;

		// If an old entity is available for reuse
		if (_dead.size() != 0)
		{
			// Get last dead entity to reuse
			nextEntity = _dead.back();
			_dead.pop_back();
		}
		else
		{
			EntityId newId = _nextEntityId++;

			// Add entity to master list of entities if this is a completely new entity
			_entityInfos.resize(newId+1);
			_entityInfos[newId] = EntityInfo();
			_entityInfos[newId]._id = newId;

			// Set tag to ""
			_world->getManager<TagManager>()->setTag(_entityInfos[newId], "");

			// Set entity ID to return
			nextEntity._id = newId;
		}

		// Make entity alive
		_entityInfos[nextEntity._id]._alive = true;

		// Set unique ID
		nextEntity._uniqueId = _nextUniqueEntityId++;
		_entityInfos[nextEntity._id]._uniqueId = nextEntity._uniqueId;

		// Create new entity
		_alive.push_back(nextEntity);

		// Update counters
		_totalCreated++;
		_count++;

		// Return entity id
		return nextEntity;
	}

	bool EntityManager::isAlive(const Entity& e)
	{
		if (e._id < (unsigned int)_count)
		{
			const EntityInfo& entityInfo = _entityInfos[e._id];

			// Check if this entity isn't dead, and if it hasn't been reused for another entity
			if (entityInfo._alive && e._uniqueId == entityInfo._uniqueId)
			{
				return true;
			}
		}

		return false;
	}

	void EntityManager::remove(EntityInfo& e)
	{
		if (!e._waitingForRemoval)
		{
			e._waitingForRemoval = true;
			_removed.push_back(e);
		}
	}

	// Remove entity immediately
	void EntityManager::removeEntity(EntityInfo& e)
	{
		// If entity is alive
		if (e._alive)
		{
			// Unset removal flag
			e._waitingForRemoval = false;

			// Murder entity
			e._alive = false;

			// Remove entity from _alive by swapping with the last element and popping off
			for (unsigned int i = 0; i < _alive.size(); ++i)
			{
				if (_alive[i] == (Entity)e)
				{
					_alive[i] = _alive[_alive.size()-1];
					_alive.pop_back();

					break;
				}
			}

			// Add to dead entities
			_dead.push_back(e);

			// Reset the component and system bitmasks
			e._componentMask.clear();

			// Remove from TagManager
			_world->getManager<TagManager>()->removeEntity(e);

			// Update counters
			_count--;
			_totalRemoved++;

			// Refresh immediately
			_world->getManager<SystemManager>()->refreshEntity(e);
		}
	}

	// Get the entity info for an entity
	// e must be a valid and living entity
	EntityInfo& EntityManager::getValidEntityInfo(const Entity& e)
	{
		// If this entity is not properly initialised
		// (e.g. created by the default constructor and not the world)
		if (e.getId() == (unsigned int)-1)
		{
			// Throw an exception
			throw UninitialisedEntity();
		}
		else if (!isAlive(e))
		{
			// Throw an exception
			throw DeadEntity();
		}

		return getEntityInfo(e);
	}

	// Get the entity info for an entity
	EntityInfo& EntityManager::getEntityInfo(const Entity& e)
	{
		// If this entity is not properly initialised
		// (e.g. created by the default constructor and not the world)
		if (e.getId() == (unsigned int)-1)
		{
			// Throw an exception
			throw UninitialisedEntity();
		}
		else if (!isAlive(e))
		{
			// Throw an exception
			throw DeadEntity();
		}

		return _entityInfos[e.getId()];
	}
}
