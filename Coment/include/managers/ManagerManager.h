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
		virtual ~ManagerManager();

		// Get a manager.
		template <typename T>
		T* getManager();

		// Add a manager
		template <typename T>
		void addManager(T* manager);

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
	void ManagerManager::addManager(T* manager)
	{
		// Get the id for this manager
		int id = T::ID;
		if (id < 0)
		{
			// Give this a new id
			T::ID = ManagerUtil::getNextID();
		}

		// Give this manager a pointer to the world
		manager->_world = _world;

		// Store a pointer to this manager
		managers.set(T::ID, manager);
	}
}

#endif