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
		// A bag of managers
		Bag<void*> managers2;

		// A hash map of managers by type
		std::hash_map<size_t, Manager*> managers;
	};

	// Template functions
	template <typename T>
	T* ManagerManager::getManager() 
	{
		return (T*)managers[typeid(T).hash_code()];
	}

	template <typename T>
	T* ManagerManager::addManager(T& manager)
	{
		//// Get the id for this manager
		//int id = T::ID;
		//if (id < 0)
		//{
		//	// Give this a new id
		//	T::ID = ManagerUtil::getNextID();
		//}

		// Initialise manager
		((Manager*)&manager)->initialise(_world);

		// Store a pointer to this manager
		//managers.set(T::ID, &manager);
		//managers[typeof(T).hash_code()] = &manager;
		managers[typeid(T).hash_code()] = &manager;

		// Return a pointer
		return &manager;
	}
}

#endif