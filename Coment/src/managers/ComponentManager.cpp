#include "coment/World.h"
#include "coment/EntityInfo.h"
#include "coment/managers/ComponentManager.h"

namespace coment
{
	ComponentManager::ComponentManager()
	{

	}

	ComponentManager::~ComponentManager()
	{
		// Iterate through component bags and deallocate memory
		for (ComponentBagMap::iterator it = _componentBags.begin(); it != _componentBags.end(); ++it)
		{
			// Don't modify the collection like this, it's not technically a Bag<Component>
			Bag<Component>* componentBag = (Bag<Component>*)(*it).second;

			// Free bag memory
			delete componentBag;
		}
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
