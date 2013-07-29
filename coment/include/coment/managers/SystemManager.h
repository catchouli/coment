#ifndef COMENT_SYSTEMMANAGER_H
#define COMENT_SYSTEMMANAGER_H

#include <string>
#include <vector>
#include <typeinfo>

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

		// Register a system with this manager
		template <typename T>
		T* registerSystem(T& system);

		// Get system of a particular type
		template <typename T>
		T* getSystem();

		// Refresh an entity with the systems
		void refresh(EntityInfo& e);

		// Update all the systems
		void update();

	private:
		// An map of system names to systems
		SystemMap _systemMap;

		// The array that contains all the systems
		std::vector<EntitySystem*> _systems;
	};

	// Register a system
	template <typename T>
	T* SystemManager::registerSystem(T& system)
	{
		// Initialise the system
		system.setWorld(_world);
		system.registered();
		system.registerComponents();
		_systems.push_back(&system);
		_systemMap[typeid(T).name()] = (EntitySystem*)&system;

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
