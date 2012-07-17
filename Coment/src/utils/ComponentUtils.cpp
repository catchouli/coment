#include "utils/ComponentUtils.h"

namespace coment
{
	ComponentType ComponentUtils::getNextType() 
	{
		return nextId++;
	}

	ComponentType ComponentUtils::nextId = 0;
}
