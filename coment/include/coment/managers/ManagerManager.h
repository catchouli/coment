#ifndef GAME_MANAGERMANAGER
#define GAME_MANAGERMANAGER

#include <string>
#include <typeinfo>

#include "Manager.h"
#include "../utils/Bag.h"
#include "../utils/Map.h"

namespace coment
{
	typedef COMENT_MAP<std::string, Manager*> ManagerMap;

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
		ManagerMap _managers;
	};

	// Template functions
	template <typename T>
	T* ManagerManager::getManager()
	{
		return (T*)_managers[typeid(T).name()];
	}

	template <typename T>
	T* ManagerManager::addManager(T& manager)
	{
		// Initialise manager
		((Manager*)&manager)->initialise(_world);

		// Store a pointer to this manager
		_managers[typeid(T).name()] = &manager;

		// Return a pointer
		return &manager;
	}
}

#endif
