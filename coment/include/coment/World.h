#ifndef COMENT_WORLD_H
#define COMENT_WORLD_H

#include <vector>

#include "Entity.h"
#include "Component.h"

#include "systems/EntityProcessingSystem.h"

#include "managers/TagManager.h"
#include "managers/GroupManager.h"
#include "managers/EntityManager.h"
#include "managers/SystemManager.h"
#include "managers/ManagerManager.h"
#include "managers/VariableManager.h"
#include "managers/ComponentManager.h"
#include "managers/ComponentTypeManager.h"

#include "exceptions/CompMapUnregistered.h"

namespace coment
{
	// The world that contains all of the entities and systems
	class World
	{
	public:
		// Constructor
		World();

		// Destructor
		~World();

		/* Entity functions */
		// Create a new entity
		Entity createEntity();

		// Check if entity is alive
		bool isAlive(const Entity& e);

		// Queue an entity for removal
		void remove(const Entity& e);

		// Refresh an entity
		void refresh(const Entity& e);

		/* Component functions */
		// Add a default constructed component to an entity
		template <typename T>
		T* addComponent(const Entity& e);

		// Get a component from an entity
		template <typename T>
		T* getComponent(const Entity& e);

		// Remove a component from an entity
		template <typename T>
		void removeComponent(const Entity& e);

		// Remove all components from an entity
		void removeComponents(const Entity& e);

		/* System functions */
		// Register a system to the system manager
		template <typename T>
		T* registerSystem(T& system);

		// Retrieve a system from the system manager
		template <typename T>
		T* getSystem();

		/* Manager functions */
		// Add a manager
		template <typename T>
		T* registerManager(T& manager);

		// Get a manager
		template <typename T>
		T* getManager();

		/* Tag functions */
		// Set tag for entity
		void setTag(const Entity& e, std::string tag);

		// Get tag by entity
		std::string getTag(const Entity& e);

		// Get entities by tag
		const std::vector<Entity>& getEntitiesByTag(std::string tag);

		/* Group functions */
		// Add group to entity
		void addGroup(const Entity& e, std::string group);

		// Remove group from entity
		void removeGroup(const Entity& e, std::string group);

		// Get groups by entity
		const std::vector<std::string>& getGroups(const Entity& e);

		// Get entities by group
		const std::vector<Entity>& getEntitiesByGroup(std::string group);

		/* Variable functions */
		// Set a value
		template <typename T>
		void setValue(std::string name, const T& value);

		// Get a value
		template <typename T>
		const T& getValue(std::string name);

		/* World functions */
		// Must be called at the start of each loop to update refreshed/deleted entities
		void loopStart();

		// Sets the delta for this frame
		void setDelta(float delta);

		// Returns the delta
		float getDelta();

		// Update all the systems
		void update();

	protected:
		/* Internal entity functions (called on loopStart) */
		// Remove entity (called automatically on queued entities)
		void removeEntity(const Entity& e);

		// Refresh entity (called automatically on queued entities)
		void refreshEntity(const Entity& e);

	private:
		// The manager instances
		TagManager _tagManager;
		GroupManager _groupManager;
		EntityManager _entityManager;
		SystemManager _systemManager;
		ManagerManager _managerManager;
		VariableManager _variableManager;
		ComponentManager _componentManager;
		ComponentTypeManager _componentTypeManager;

		// Entities due to be removed
		std::vector<Entity> _removed;

		// Entities due to be refreshed
		std::vector<Entity> _refreshed;
	};

	// Add a manager
	template <typename T>
	T* World::registerManager(T& manager)
	{
		return _managerManager.registerManager(manager);
	}

	// Get a manager
	template <typename T>
	T* World::getManager()
	{
		return _managerManager.getManager<T>();
	}

	// Add the component to the component manager
	template <typename T>
	T* World::addComponent(const Entity& e)
	{
		// Add component
		T* component = _componentManager.addComponent<T>(_entityManager.getEntityInfo(e));

		// Queue entity for refresh
		refresh(e);

		// Return component
		return component;
	}

	// Register a system with the system manager
	template <typename T>
	T* World::registerSystem(T& system)
	{
		return _systemManager.registerSystem(system);
	}

	// Retrieve a system from the system manager
	template <typename T>
	T* World::getSystem()
	{
		return _systemManager.getSystem<T>();
	}

	// Get a component from an entity
	template <typename T>
	T* World::getComponent(const Entity& e)
	{
		return _componentManager.getComponent<T>(_entityManager.getEntityInfo(e));
	}

	// Remove a component from an entity
	template <typename T>
	void World::removeComponent(const Entity& e)
	{
		// Remove component
		_componentManager.removeComponent<T>(_entityManager.getEntityInfo(e));

		// Refresh entity immediately (refreshEntity instead of refresh)
		// Otherwise, somebody might try and update a system before loopStart,
		// Causing a null pointer exception
		refreshEntity(e);
	}

	/* Inline variable functions */
	template <typename T>
	void World::setValue(std::string name, const T& value)
	{
		_variableManager.setValue<T>(name, value);
	}

	template <typename T>
	const T& World::getValue(std::string name)
	{
		return _variableManager.getValue<T>(name);
	}
}

#endif /* COMENT_WORLD_H */
