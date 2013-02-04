#include "managers/Manager.h"

namespace coment
{
	Manager::Manager()
		: _initialised(false)
	{

	}

	void Manager::initialise(World* world)
	{
		_world = world;

		_initialised = true;
	}
	
	bool Manager::getInitialised()
	{
		return _initialised;
	}
}
