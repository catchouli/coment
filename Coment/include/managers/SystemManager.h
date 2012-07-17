#ifndef __SYSTEMMANAGER_H__
#define __SYSTEMMANAGER_H__

#include <hash_map>

#include "managers/Manager.h"
#include "../utils/Bag.h"
#include "systems/EntitySystem.h"

namespace coment
{
	// Contains all the systems added to the world
	class SystemManager
		: public Manager<SystemManager>
	{
	public:
		SystemManager();

		// Register a system with this manager
		template <typename T>
		void registerSystem(T& system);

		// Refresh an entity with the systems
		void refresh(EntityInfo& e);

		// Update all the systems.
		void update();

	private:
		// The hash map that contains all the systems
		Bag<EntitySystem*> _systemMap;
	};

	// Registering a system
	template <typename T>
	void SystemManager::registerSystem(T& system)
	{
		// Set the system's world to this ones
		system.setWorld(_world);
		_systemMap.add(&system);
	}
}

#endif /* __SYSTEMMANAGER_H__ */
