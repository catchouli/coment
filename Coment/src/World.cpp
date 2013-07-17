#include "coment/World.h"

namespace coment
{
	World::World()
		: _delta(0)
	{
		// Create manager manager
		_managerManager.initialise(this);

		// Initialise default managers
		_managerManager.addManager(_tagManager);
		_managerManager.addManager(_systemManager);
		_managerManager.addManager(_entityManager);
		_managerManager.addManager(_componentTypeManager);
		_managerManager.addManager(_componentManager);
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

		// Reset entity's tag
		//setTag(e, std::string(""));
	}

	void World::setTag(Entity e, std::string tag)
	{
		_tagManager.setTag(_entityManager.getEntityInfo(e), tag);
	}

	std::string World::getTag(Entity e)
	{
		return _tagManager.getTag(_entityManager.getEntityInfo(e));
	}


	void World::refreshEntity(Entity e)
	{
		// Get the entity info
		EntityInfo& info = _entityManager.getEntityInfo(e);

		// Refresh the entity
		_systemManager.refresh(info);
	}

	void World::removeComponents(Entity e)
	{
		_componentManager.removeComponents(_entityManager.getEntityInfo(e));
	}
}
