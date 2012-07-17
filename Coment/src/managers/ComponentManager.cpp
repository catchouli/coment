#include "EntityInfo.h"
#include "managers/ComponentManager.h"

namespace coment
{
	// Constructor
	ComponentManager::ComponentManager()
	{
		init();
	}

	// Initialization function
	void ComponentManager::init()
	{

	}

	// Remove all the components from an entity
	void ComponentManager::removeComponents(EntityInfo& e)
	{
		e._systemMask.clear();
	}
}
