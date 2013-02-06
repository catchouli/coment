#include "EntityInfo.h"
#include "managers/ComponentManager.h"

namespace coment
{
	ComponentManager::ComponentManager()
	{
		init();
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
