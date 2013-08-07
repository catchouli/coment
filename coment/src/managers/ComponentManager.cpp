#include "coment/World.h"
#include "coment/EntityInfo.h"
#include "coment/managers/ComponentManager.h"

namespace coment
{
	void ComponentManager::onRegistered()
	{
		_world->registerManager(_componentTypeManager);
	}

	// Remove all the components from an entity
	void ComponentManager::removeComponents(EntityInfo& e)
	{
		e.removeComponents();
	}
}
