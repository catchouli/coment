#ifndef __WORLD_H__
#define __WORLD_H__

#include "Entity.h"
#include "Component.h"

#include "managers/EntityManager.h"
#include "managers/SystemManager.h"
#include "managers/ComponentManager.h"
#include "managers/GroupManager.h"
#include "managers/ManagerManager.h"

#include "exceptions/CompMapUnregistered.h"

namespace coment
{
	// The world that contains all of the entities and systems
	class World
	{
	public:
		// Constructor
		World();

		// Add a manager
		template <typename T>
		void addManager(T* manager);
		
		// Get a manager
		template <typename T>
		T& getManager();

		// Set a manager.
		template <typename T>
		void setManager(T& manager);

		EntityManager& getEntityManager();
		SystemManager& getSystemManager();
		ComponentManager& getComponentManager();
		GroupManager& getGroupManager();
		
		// Create a new entity
		Entity createEntity();
		
		// Add a component to an entity
		template <typename T>
		T* addComponent(Entity e, T c);

		// Get a component from an entity
		template <typename T>
		T* getComponent(Entity e);

		// Remove a component from an entity
		template <typename T>
		void removeComponent(Entity e);
		
		// Remove all components from an entity
		void removeComponents(Entity e);

		// Register a system to the system manager
		template <typename T>
		void registerSystem(T& system);

		// Must be called at the start of each loop to update refreshed
		// and deleted entities
		void loopStart();

		// Sets the delta for this frame
		void setDelta(float delta);

		// Returns the delta
		float getDelta();
		
		// Update all the systems.
		void update();

		// Queue an entity for removal
		void remove(Entity e);

		// Refresh an entity
		void refresh(Entity e);

	protected:
		// Remove entity (called automatically on queued entities)
		void removeEntity(Entity e);

		// Refresh entity (called automatically on queued entities)
		void refreshEntity(Entity e);
		
	private:
		// The manager instances
		EntityManager _entityManager;
		SystemManager _systemManager;
		ComponentManager _componentManager;
		GroupManager _groupManager;
		ManagerManager _managerManager;

		// Entities due to be removed
		Bag<Entity> _removed;

		// Entities due to be refreshed
		Bag<Entity> _refreshed;

		// The difference in time since the last frame
		float _delta;
	};

	// Add a manager
	template <typename T>
	void World::addManager(T* manager)
	{
		_managerManager.addManager(manager);
	}

	// Get a manager
	template <typename T>
	T& World::getManager()
	{
		return *_managerManager.getManager<T>();
	}

	// Set a manager
	template <typename T>
	void World::setManager(T& manager)
	{
		_managerManager.addManager(&manager);
	}

	template <typename T>
	T* World::addComponent(Entity e, T c)
	{
		// Add the component to the component manager
		return _componentManager.addComponent(_entityManager.getEntityInfo(e), c);
	}

	// Get a component from an entity
	template <typename T>
	T* World::getComponent(Entity e)
	{
		return _componentManager.getComponent<T>(_entityManager.getEntityInfo(e));
	}

	// Remove a component from an entity
	template <typename T>
	void removeComponent(Entity e);

	template <typename T>
	void World::registerSystem(T& system)
	{
		// Register a system with the system manager
		_systemManager.registerSystem(system);
	}
}

#endif /* __WORLD_H__ */
