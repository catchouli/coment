#include "managers/Manager.h"

namespace coment
{
	// Intialize the next id
	unsigned int ManagerUtil::nextID = 0;

	// Get the next id;
	unsigned int ManagerUtil::getNextID() 
	{
		return nextID++;
	}
}
