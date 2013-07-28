#include "coment/World.h"

#include "coment/utils/Functions.h"

namespace coment
{
	World::World()
	{
		// Create manager manager
		_managerManager.initialise(this);

		// Initialise default managers
		_managerManager.registerManager(_tagManager);
		_managerManager.registerManager(_systemManager);
		_managerManager.registerManager(_entityManager);
		_managerManager.registerManager(_variableManager);
		_managerManager.registerManager(_componentTypeManager);
		_managerManager.registerManager(_componentManager);

		// Initialise delta time
		setDelta(0.0f);
	}

	World::~World()
	{

	}

	Entity World::createEntity()
	{
		// Request an unused entity from the entity manager
		return _entityManager.createEntity();
	}

	bool World::isAlive(const Entity& e)
	{
		return _entityManager.isAlive(e);
	}

	void World::loopStart()
	{
		// Remove entities queued for removal
		for (std::vector<Entity>::iterator it = _removed.begin(); it != _removed.end(); ++it)
		{
			// Remove entity from world
			removeEntity(*it);
		}

		_removed.clear();

		// Refresh entities queued for refresh
		// Make sure to do this after updating removed entities, as entities are refreshed after being removed
		for (std::vector<Entity>::iterator it = _refreshed.begin(); it != _refreshed.end(); ++it)
		{
			refreshEntity(*it);
		}

		_refreshed.clear();
	}

	void World::setDelta(float delta)
	{
		setValue<float>("delta", delta);
	}

	float World::getDelta()
	{
		return getValue<float>("delta");
	}

	void World::update()
	{
		_systemManager.update();
	}

	void World::remove(const Entity& e)
	{
		EntityInfo& entityInfo = _entityManager.getEntityInfo(e);

		// Add an entity to the removal list and set a boolean flag so that it doesn't get added twice
		if (!entityInfo._waitingForRemoval)
		{
			entityInfo._waitingForRemoval = true;
			_removed.push_back(e);
		}
	}

	void World::refresh(const Entity& e)
	{
		EntityInfo& entityInfo = _entityManager.getEntityInfo(e);

		// Add an entity to the refreshed list and set a boolean flag so that it doesn't get added twice
		if (!entityInfo._waitingForRefresh)
		{
			entityInfo._waitingForRefresh = true;
			_refreshed.push_back(e);
		}
	}

	void World::removeEntity(const Entity& e)
	{
		// Get the entity info
		EntityInfo& info = _entityManager.getEntityInfo(e);

		// Unset removal flag
		info._waitingForRemoval = false;

		// Remove the entity
		_entityManager.removeEntity(info);

		// Refresh the entity immediately (must be refreshEntity instead of refresh)
		refreshEntity(e);
	}

	void World::setTag(const Entity& e, std::string tag)
	{
		_tagManager.setTag(_entityManager.getEntityInfo(e), tag);
	}

	std::string World::getTag(const Entity& e)
	{
		return _tagManager.getTag(_entityManager.getEntityInfo(e));
	}

	const std::vector<Entity>& World::getEntitiesByTag(std::string tag)
	{
		return _tagManager.getEntities(tag);
	}

	void World::refreshEntity(const Entity& e)
	{
		// Get entity info
		EntityInfo& info = _entityManager._entityInfos[e.getId()];

		// Unset refresh flag
		info._waitingForRefresh = false;

		// Refresh the entity
		_systemManager.refresh(info);
	}

	void World::removeComponents(const Entity& e)
	{
		// Remove component
		_componentManager.removeComponents(_entityManager.getEntityInfo(e));

		// Refresh entity immediately (refreshEntity instead of refresh)
		// Otherwise, somebody might try and update a system before loopStart,
		// Causing a null pointer exception
		refreshEntity(e);
	}
}
