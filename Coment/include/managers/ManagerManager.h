#ifndef GAME_MANAGERMANAGER
#define GAME_MANAGERMANAGER

#include <hash_map>
#include "Manager.h"
#include "../utils/Bag.h"

namespace coment
{
	class ManagerManager : public Manager<ManagerManager>
	{
	public:
		ManagerManager();

		// Get a manager.
		template <typename T>
		T* getManager();

		// Add a manager
		template <typename T>
		T* addManager();

		// Add a manager
		template <typename T>
		T* addManager(T* manager);

	private:
		// A bag of managers
		Bag<void*> managers;
	};

	// Template functions
	template <typename T>
	T* ManagerManager::getManager() 
	{
		return (T*)managers[T::ID];
	}

	template <typename T>
	T* ManagerManager::addManager()
	{
		return addManager(new T());
	}

	template <typename T>
	T* ManagerManager::addManager(T* manager)
	{
		// Get the id for this manager
		int id = T::ID;
		if (id < 0)
		{
			// Give this a new id
			T::ID = ManagerUtil::getNextID();
		}

		// Initialise manager
		((Manager*)manager)->initialise(_world);

		// Store a pointer to this manager
		managers.set(T::ID, manager);

		// Return a pointer
		return manager;
	}
}

#endif