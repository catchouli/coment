#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <hash_map>
#include <memory>

#include "Manager.h"
#include "../Component.h"
#include "../utils/Bag.h"
#include "../exceptions/CompMapUnregistered.h"

namespace coment
{
	typedef std::hash_map<size_t, void*> ComponentBagMap;

	// The component manager keeps track of which components are attached to which entities
	class ComponentManager
		: public Manager
	{
	public:
		ComponentManager();
		~ComponentManager();

		// Init
		void init();

		// Add a component onto an entity
		template <typename T>
		T* addComponent(EntityInfo& e);

		// Get a component from an entity
		template <typename T>
		T* getComponent(EntityInfo& e);

		// Remove a component from an entity
		template <typename T>
		void removeComponent(EntityInfo& e);

		// Remove all the components from an entity
		void removeComponents(EntityInfo& e);

	protected:
		// Get a bag for a component type
		template <typename T>
		Bag<T>* getComponentBag();

	private:
		// A map of component bags
		ComponentBagMap _componentBags;
	};

	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e)
	{
		Bag<T>* components = getComponentBag<T>();
		ComponentType componentType = _world->getManager<ComponentTypeManager>()->getComponentType<T>();

		// Add the component to it
		components->set(e.getId(), T());

		// Set the entity's components bitmask
		e.addComponent(componentType);
		
		// Return the component we just added
		return getComponent<T>(e);
	}

	// Get a component from an entity
	template <typename T>
	T* ComponentManager::getComponent(EntityInfo& e)
	{
		Bag<T>* components = getComponentBag<T>();

		// If this entity doesn't have this component return null
		if (!e._componentMask[_world->getManager<ComponentTypeManager>()->getComponentType<T>()])
			return NULL;

		return &((*components)[e.getId()]);
	}

	// Remove a component from an entity
	template <typename T>
	void ComponentManager::removeComponent(EntityInfo& e)
	{
		e._systemMask.clear(T::type);
	}

	// Get a bag for a component type
	template <typename T>
	Bag<T>* ComponentManager::getComponentBag()
	{
		Bag<T>* components = (Bag<T>*)_componentBags[typeid(T).hash_code()];

		// If this type doesn't have a bag yet
		if (components == nullptr)
		{
			// Create one
			components = new Bag<T>();

			// Store it in hash map
			_componentBags[typeid(T).hash_code()] = components;
		}

		return components;
	}
}

#endif /* __COMPONENTMAP_H__ */
