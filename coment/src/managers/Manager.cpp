#include "coment/managers/Manager.h"

namespace coment
{
	Manager::Manager()
		: _world(0), _initialised(false)
	{

	}

	void Manager::onRegistered()
	{

	}

	bool Manager::getInitialised()
	{
		return _initialised;
	}
}
