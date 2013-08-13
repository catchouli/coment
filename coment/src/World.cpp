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
		EntityInfo& entityInfo = _entityManager.getValidEntityInfo(e);

		// Queue entity for removal
		_entityManager.remove(entityInfo);
	}

	// Queue an entity to be refreshed
	void World::refresh(const Entity& e)
	{
		EntityInfo& entityInfo = _entityManager.getEntityInfo(e);

		// Queue entity to be refreshed
		_systemManager.refresh(entityInfo);
	}

	/* Tag functions */
	// Set the tag of an entity
	void World::setTag(const Entity& e, std::string tag)
	{
		_tagManager.setTag(_entityManager.getValidEntityInfo(e), tag);
	}

	// Get the tag of an entity
	std::string World::getTag(const Entity& e)
	{
		return _tagManager.getTag(_entityManager.getValidEntityInfo(e));
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
		_groupManager.addGroup(_entityManager.getValidEntityInfo(e), group);
	}

	// Remove entity from group
	void World::removeGroup(const Entity& e, std::string group)
	{
		_groupManager.removeGroup(_entityManager.getValidEntityInfo(e), group);
	}

	// Remove entity from all groups
	void World::removeGroups(const Entity& e)
	{
		_groupManager.removeGroups(_entityManager.getValidEntityInfo(e));
	}

	// Check if entity is in group
	bool World::isInGroup(const Entity& e, std::string group)
	{
		return _groupManager.isInGroup(_entityManager.getValidEntityInfo(e), group);
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
		EntityInfo& entityInfo = _entityManager.getValidEntityInfo(e);

		// Remove component
		_componentManager.removeComponents(entityInfo);

		// Refresh entity immediately (refreshEntity instead of refresh)
		// Otherwise, somebody might try and update a system before loopStart,
		// Causing a null pointer exception
		_systemManager.refreshEntity(entityInfo);
	}

	/* Misc functions */
	// Start iteration of main loop - removes and refreshes queued entities
	void World::loopStart()
	{
		_entityManager.loopStart();
		_systemManager.loopStart();
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
}
