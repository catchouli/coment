#ifndef GAME_MANAGERMANAGER
#define GAME_MANAGERMANAGER

#include <string>
#include <typeinfo>
#include <tr1/unordered_map>

#include "Manager.h"
#include "../utils/Bag.h"

namespace coment
{
//	typedef std::tr1::unordered_map<std::string, Manager*> ManagerMap;

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
		std::tr1::unordered_map<std::string, Manager*> _managers;
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
