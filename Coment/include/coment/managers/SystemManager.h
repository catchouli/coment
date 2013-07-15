#ifndef __SYSTEMMANAGER_H__
#define __SYSTEMMANAGER_H__

#include <typeinfo>
#include <tr1/unordered_map>

#include "../managers/Manager.h"
#include "../systems/EntitySystem.h"
#include "../utils/Bag.h"
#include "../utils/HashGenerator.h"

namespace coment
{
	typedef std::tr1::unordered_map<size_t, EntitySystem*> SystemMap;

	// Contains all the systems added to the world
	class SystemManager
		: public Manager
	{
	public:
		SystemManager();

		// Register a system with this manager
		template <typename T>
		T* addSystem(T& system);

		// Get system of a particular type
		template <typename T>
		T* getSystem();

		// Refresh an entity with the systems
		void refresh(EntityInfo& e);

		// Update all the systems
		void update();

	private:
		// An array of systems by ID
		SystemMap _systems;

		// The hash map that contains all the systems
		Bag<EntitySystem*> _systemMap;
	};

	// Register a system
	template <typename T>
	T* SystemManager::addSystem(T& system)
	{
		// Initialise the system
		system.setWorld(_world);
		system.onRegistered();
		system.registerComponents();
		_systemMap.add(&system);
		_systems[HashGenerator::hash<T>()] = (EntitySystem*)&system;

		return &system;
	}

	// Get system of a particular type
	template <typename T>
	T* SystemManager::getSystem()
	{
		return (T*)_systems[HashGenerator::hash<T>()];
	}
}

#endif /* __SYSTEMMANAGER_H__ */
