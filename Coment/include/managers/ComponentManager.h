#include <iostream>

#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <memory>

#include "Manager.h"

#include "../Component.h"

#include "../utils/Bag.h"

#include "../exceptions/CompMapUnregistered.h"

namespace coment
{
	// The component manager keeps track of which components are attached to which entities
	class ComponentManager
		: public Manager<ComponentManager>
	{
	public:
		// Constructor
		ComponentManager();
		
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
	};

	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e)
	{
		// If the component is of a new type
		if (T::type == -1)
		{
			// Assign the component type the next available 
			T::type = ComponentUtils::getNextType();
		}

		// Add the component to it
		T::components.set(e.getId(), T());

		// Set the entity's components bitmask
		e.addComponent(T::type);

		// Return the component we just added
		return getComponent<T>(e);
	}

	// Get a component from an entity
	template <typename T>
	T* ComponentManager::getComponent(EntityInfo& e)
	{
		// If component type is unregistered, throw an exception
		if (T::type == -1)
			throw CompMapUnregistered();

		// If this entity doesn't have this component return null
		if (!e._componentMask[T::type])
			return NULL;

		return &T::components[e.getId()];
	}

	// Remove a component from an entity
	template <typename T>
	void ComponentManager::removeComponent(EntityInfo& e)
	{
		e._systemMask.clear(T::type);
	}
}

#endif /* __COMPONENTMAP_H__ */
