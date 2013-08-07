#ifndef COMENT_MANAGER_H
#define COMENT_MANAGER_H

namespace coment
{
	class World;

	class Manager
	{
	public:
		Manager();

		// Called when this manager has been registered with the world
		virtual void onRegistered();

		// Get whether or not we are already initialised
		bool getInitialised();

	protected:
		friend class World;
		friend class ManagerManager;

		// The parent world.
		World* _world;

	private:
		// Whether or not we are initialized.
		bool _initialised;
	};
}

#endif /* COMENT_MANAGER_H */
