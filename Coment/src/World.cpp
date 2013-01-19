#include "World.h"

namespace coment
{
	World::World()
		: _delta(0)
	{
		_entityManager.initialise(this);
		_systemManager.initialise(this);
		_componentManager.initialise(this);
		_groupManager.initialise(this);
		_managerManager.initialise(this);

		// Add managers to manager manager.
		_managerManager.addManager(&_entityManager);
		_managerManager.addManager(&_systemManager);
		_managerManager.addManager(&_componentManager);
		_managerManager.addManager(&_groupManager);
		_managerManager.addManager(&_managerManager);
	}

	EntityManager& World::getEntityManager()
	{
		return _entityManager;
	}

	SystemManager& World::getSystemManager()
	{
		return _systemManager;
	}

	ComponentManager& World::getComponentManager()
	{
		return _componentManager;
	}

	GroupManager& World::getGroupManager()
	{
		return _groupManager;
	}

	Entity World::createEntity()
	{
		// Request an unused entity from the entity manager
		return _entityManager.createEntity();
	}	

	void World::loopStart()
	{

		// Remove entities queued for removal
		for (unsigned int i = 0; i < _removed.size(); ++i)
		{
			removeEntity(_removed[i]);
		}

		_removed.clear();

		// Refresh entities queued for refresh
		// Make sure to do this after updating removed entities, as entities are refreshed after being removed
		for (unsigned int i = 0; i < _refreshed.size(); ++i)
		{
			refreshEntity(_refreshed[i]);
		}

		_refreshed.clear();
	}

	void World::setDelta(float delta)
	{
		_delta = delta;
	}

	float World::getDelta()
	{
		return _delta;
	}

	void World::update()
	{
		_systemManager.update();
	}

	void World::remove(Entity e)
	{
		_removed.push_back(e);
	}

	void World::refresh(Entity e) 
	{
		_refreshed.push_back(e);
	}

	void World::removeEntity(Entity e)
	{		
		// Get the entity info.
		EntityInfo& info = _entityManager.getEntityInfo(e);

		// Remove the entity.
		_entityManager.removeEntity(info);

		// Refresh systems concerned with this entities
		refresh(e);

		// Remove entity from any groups it's in
		_groupManager.remove(e);
	}

	void World::refreshEntity(Entity e)
	{
		// Get the entity info
		EntityInfo& info = _entityManager.getEntityInfo(e);

		// Refresh the entity
		_systemManager.refresh(info);
	}
}
