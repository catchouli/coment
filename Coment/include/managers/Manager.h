#ifndef __MANAGER_H__
#define __MANAGER_H__

namespace coment
{
	class World;

	class ManagerUtil 
	{
	public:

	protected:
		friend class ManagerManager;
		
		// The next id to use.
		static unsigned int nextID;

		// Get a the next id.
		static unsigned int getNextID();

	private:
	};

	template <typename T>
	class Manager
	{
	public:
		// Constructors
		Manager();
		
		// Initialize this manager.
		virtual void initialise(World* world);

		// Get whether or not we are already initialized.
		bool getInitialised();

	protected:
		// Friends
		friend class ManagerManager;

		// The parent world.
		World* _world;

		// The static ID for this manager.
		static int ID;

	private:
		// Whether or not we are initialized.
		bool _initialised;
	};

	// Initialize the ID
	template <typename T>
	int Manager<T>::ID = -1;

	template <typename T>
	Manager<T>::Manager()
		: _initialised(false)
	{

	}

	template <typename T>
	void Manager<T>::initialise(World* world)
	{
		_world = world;

		_initialised = true;
	}
	
	template <typename T>
	bool Manager<T>::getInitialised()
	{
		return _initialised;
	}
}

#endif /* __MANAGER_H__ */
