#include "World.h"

namespace coment
{
	World::World()
		: _delta(0)
	{
		// Create manager manager
		_managerManager.initialise(this);
		
		// Initialise default managers
		_managerManager.addManager(_groupManager);
		_managerManager.addManager(_systemManager);
		_managerManager.addManager(_entityManager);
		_managerManager.addManager(_componentManager);
		_managerManager.addManager(_componentTypeManager);
	}

	World::~World()
	{

	}

	Entity World::createEntity()
	{
		// Request an unused entity from the entity manager
		return _entityManager.createEntity();
	}	

	void World::loopStart()
	{

		// Remove entities queued for removal
		for (unsigned int i = 0; i < _removed.getSize(); ++i)
		{
			removeEntity(_removed[i]);
		}

		_removed.clear();

		// Refresh entities queued for refresh
		// Make sure to do this after updating removed entities, as entities are refreshed after being removed
		for (unsigned int i = 0; i < _refreshed.getSize(); ++i)
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
		_removed.add(e);
	}

	void World::refresh(Entity e) 
	{
		_refreshed.add(e);
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
