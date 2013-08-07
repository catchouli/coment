#include "coment/World.h"

#include "coment/utils/Functions.h"

namespace coment
{
	// Initialise managers and register them
	World::World()
	{
		// Create manager manager
		_managerManager._world = this;
		_managerManager._initialised = true;

		// Initialise default managers
		_managerManager.registerManager(_tagManager);
		_managerManager.registerManager(_systemManager);
		_managerManager.registerManager(_entityManager);
		_managerManager.registerManager(_variableManager);
		_managerManager.registerManager(_componentManager);

		// Initialise delta time
		setDelta(0.0f);
	}

	/* Entity functions */
	// Create a new entity
	Entity World::createEntity()
	{
		// Request an unused entity from the entity manager
		return _entityManager.createEntity();
	}

	// Check if an entity is alive
	bool World::isAlive(const Entity& e)
	{
		return _entityManager.isAlive(e);
	}

	// Queue and entity for removal
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

	// Queue an entity to be refreshed
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

	/* Tag functions */
	// Set the tag of an entity
	void World::setTag(const Entity& e, std::string tag)
	{
		_tagManager.setTag(_entityManager.getEntityInfo(e), tag);
	}

	// Get the tag of an entity
	std::string World::getTag(const Entity& e)
	{
		return _tagManager.getTag(_entityManager.getEntityInfo(e));
	}

	// Get the entities with a tag
	const std::vector<Entity>& World::getEntitiesByTag(std::string tag)
	{
		return _tagManager.getEntities(tag);
	}

	/* Group functions */
	// Add entity to group
	void World::addGroup(const Entity& e, std::string group)
	{
		_groupManager.addGroup(_entityManager.getEntityInfo(e), group);
	}

	// Remove entity from group
	void World::removeGroup(const Entity& e, std::string group)
	{
		_groupManager.removeGroup(_entityManager.getEntityInfo(e), group);
	}

	// Remove entity from all groups
	void World::removeGroups(const Entity& e)
	{
		_groupManager.removeGroups(_entityManager.getEntityInfo(e));
	}

	// Check if entity is in group
	bool World::isInGroup(const Entity& e, std::string group)
	{
		return _groupManager.isInGroup(_entityManager.getEntityInfo(e), group);
	}

	// Get entities by group
	const std::vector<Entity>& World::getEntitiesByGroup(std::string group)
	{
		return _groupManager.getEntitiesByGroup(group);
	}

	/* Misc */
	// Remove all components from an entity and refresh it
	void World::removeComponents(const Entity& e)
	{
		// Remove component
		_componentManager.removeComponents(_entityManager.getEntityInfo(e));

		// Refresh entity immediately (refreshEntity instead of refresh)
		// Otherwise, somebody might try and update a system before loopStart,
		// Causing a null pointer exception
		refreshEntity(e);
	}

	/* Misc functions */
	// Start iteration of main loop - removes and refreshes queued entities
	void World::loopStart()
	{
		// Remove entities queued for removal
		for (std::vector<Entity>::iterator it = _removed.begin(); it != _removed.end(); ++it)
		{
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

	// Set the delta time
	void World::setDelta(float delta)
	{
		setValue<float>("delta", delta);
	}

	// Get the delta time
	float World::getDelta()
	{
		return getValue<float>("delta");
	}

	// Update all systems
	void World::update()
	{
		_systemManager.update();
	}

	/* Protected */
	// Remove an entity immediately
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

	// Refresh an entity immediately
	void World::refreshEntity(const Entity& e)
	{
		// Get entity info
		EntityInfo& info = _entityManager._entityInfos[e.getId()];

		// Unset refresh flag
		info._waitingForRefresh = false;

		// Refresh the entity
		_systemManager.refresh(info);
	}
}
