#include "coment/World.h"
#include "coment/EntityInfo.h"
#include "coment/managers/ComponentManager.h"

namespace coment
{
	ComponentManager::ComponentManager()
	{

	}

	// Initialise this manager once it's registered with the world
	void ComponentManager::onRegistered()
	{
		_componentTypeManager = _world->getManager<ComponentTypeManager>();
	}

	// Remove all the components from an entity
	void ComponentManager::removeComponents(EntityInfo& e)
	{
		e.removeComponents();
	}
}
