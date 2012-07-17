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
		void addComponent(EntityInfo& e, T component);

		// Get a component from an entity
		template <typename T>
		T* getComponent(EntityInfo& e);

		// Remove a component from an entity
		template <typename T>
		void removeComponent(EntityInfo& e);

		// Remove all the components from an entity
		void removeComponents(EntityInfo& e);

	private:
		// A bag containing bags of components
		Bag<void*> _componentsByType;
	};

	// Add a component to an entity
	template <typename T>
	void ComponentManager::addComponent(EntityInfo& e, T c)
	{
		// Get bag of components for this type
		Bag<T>* componentMap = NULL;

		// If the component is of a new type
		if (T::type == -1)
		{
			// Assign the component type the next available 
			T::type = ComponentUtils::getNextType();
		}

		// Add a bag if this component hasn't been mapped
		if (_componentsByType.get(c.type) == NULL) 
		{
			// Create a component map for this type
			componentMap = new Bag<T>();

			// Add the component map to our collection
			_componentsByType.set(c.type, componentMap);
		}
		componentMap = (Bag<T>*)_componentsByType.get(c.type);

		// Add the component to it
		componentMap->set(e.getId(), c);

		// Set the entity's components bitmask
		e.addComponent(T::type);
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

		// Otherwise, return the component
		Bag<T>* _componentMap = (Bag<T>*)_componentsByType.get(T::type);
		
		return &_componentMap->get(e.getId());
	}

	// Remove a component from an entity
	template <typename T>
	void ComponentManager::removeComponent(EntityInfo& e)
	{
		e._systemMask.clear(T::type);
	}
}

#endif /* __COMPONENTMAP_H__ */
