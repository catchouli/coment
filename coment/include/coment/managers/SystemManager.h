#ifndef COMENT_SYSTEMMANAGER_H
#define COMENT_SYSTEMMANAGER_H

#include <string>
#include <vector>
#include <typeinfo>

#include "../Entity.h"
#include "../managers/Manager.h"
#include "../systems/EntitySystem.h"
#include "../utils/Map.h"

namespace coment
{
	typedef std::tr1::unordered_map<std::string, EntitySystem*> SystemMap;

	// Contains all the systems added to the world
	class SystemManager
		: public Manager
	{
	public:
		SystemManager();

		// Called at the start of each loop, handles entity refreshing
		void loopStart();

		// Register a system with this manager
		template <typename T>
		T* registerSystem(T& system);

		// Get system of a particular type
		template <typename T>
		T* getSystem();

		// Queue an entity to be refreshed
		void refresh(EntityInfo& e);

		// Update all the systems
		void update();

	protected:
		friend class World;
		friend class EntityManager;

		// Immediately refresh an entity
		void refreshEntity(EntityInfo& e);

	private:
		// An map of system names to systems
		SystemMap _systemMap;

		// Entities waiting to be refreshed
		std::vector<Entity> _refreshed;

		// The array that contains all the systems
		std::vector<EntitySystem*> _systems;
	};

	// Register a system
	template <typename T>
	T* SystemManager::registerSystem(T& system)
	{
		// Initialise the system
		system.setWorld(_world);
		system.registerComponents();
		_systems.push_back(&system);
		_systemMap[typeid(T).name()] = (EntitySystem*)&system;
		((EntitySystem*)&system)->onRegistered();

		return &system;
	}

	// Get system of a particular type
	template <typename T>
	T* SystemManager::getSystem()
	{
		return (T*)_systemMap[typeid(T).name()];
	}
}

#endif /* COMENT_SYSTEMMANAGER_H */
