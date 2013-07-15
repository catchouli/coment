#ifndef GAME_MANAGERMANAGER
#define GAME_MANAGERMANAGER

#include <typeinfo>
#include <tr1/unordered_map>

#include "Manager.h"
#include "../utils/Bag.h"
#include "../utils/HashGenerator.h"

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
		std::tr1::unordered_map<size_t, Manager*> _managers;
	};

	// Template functions
	template <typename T>
	T* ManagerManager::getManager()
	{
		return (T*)_managers[HashGenerator::hash<T>()];
	}

	template <typename T>
	T* ManagerManager::addManager(T& manager)
	{
		// Initialise manager
		((Manager*)&manager)->initialise(_world);

		// Store a pointer to this manager
		_managers[HashGenerator::hash<T>()] = &manager;

		// Return a pointer
		return &manager;
	}
}

#endif
