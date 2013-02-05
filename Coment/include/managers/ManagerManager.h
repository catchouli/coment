#ifndef GAME_MANAGERMANAGER
#define GAME_MANAGERMANAGER

#include <hash_map>
#include "Manager.h"
#include "../utils/Bag.h"

namespace coment
{
	class ManagerManager : public Manager
	{
	public:
		ManagerManager();

		// Get a manager.
		template <typename T>
		T* getManager();
		
		// Add a manager
		template <typename T>
		T* addManager(T& manager);

	private:
		// A hash map of managers by type
		std::hash_map<size_t, Manager*> _managers;
	};

	// Template functions
	template <typename T>
	T* ManagerManager::getManager() 
	{
		return (T*)_managers[typeid(T).hash_code()];
	}

	template <typename T>
	T* ManagerManager::addManager(T& manager)
	{
		// Initialise manager
		((Manager*)&manager)->initialise(_world);

		// Store a pointer to this manager
		_managers[typeid(T).hash_code()] = &manager;

		// Return a pointer
		return &manager;
	}
}

#endif