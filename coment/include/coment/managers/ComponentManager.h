#ifndef COMENT_COMPONENTMANAGER_H
#define COMENT_COMPONENTMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

#include "Manager.h"
#include "../Component.h"
#include "../utils/Map.h"
#include "../utils/SharedPtr.h"
#include "../managers/ComponentTypeManager.h"
#include "../exceptions/CompMapUnregistered.h"

namespace coment
{
#ifdef COMENT_CONFIG_HAS_CPP11
	typedef std::unordered_map<std::string, std::shared_ptr<void> > ComponentBagMap;
	typedef std::shared_ptr<void> shared_ptr;
#else
	typedef std::tr1::unordered_map<std::string, std::tr1::shared_ptr<void> > ComponentBagMap;
	typedef std::tr1::shared_ptr<void> shared_ptr;

#endif

	// The component manager keeps track of which components are attached to which entities
	class ComponentManager
		: public Manager
	{
	public:
		// Add a component onto an entity
		template <typename T>
		T* addComponent(EntityInfo& e);

		// Add a component onto an entity
		template <typename T>
		T* addComponent(EntityInfo& e, const T& value);

		// Get a component from an entity
		template <typename T>
		T* getComponent(EntityInfo& e);

		// Check if entity has component
		template <typename T>
		bool hasComponent(EntityInfo& e);

		// Remove a component from an entity
		template <typename T>
		void removeComponent(EntityInfo& e);

		// Remove all the components from an entity
		void removeComponents(EntityInfo& e);

		// Register component type manager when registered with world
		virtual void onRegistered();

	protected:
		// Get a bag for a component type
		template <typename T>
		std::vector<T>* getComponentBag();

	private:
		// Component type manager
		ComponentTypeManager _componentTypeManager;

		// A map of component bags
		ComponentBagMap _componentBags;
	};

	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e)
	{
		std::vector<T>* components = getComponentBag<T>();
		ComponentType componentType = _componentTypeManager.getComponentType<T>();

		// Add the component to it
		const unsigned int size = std::max<unsigned int>(e.getId()+1, components->size());
		components->resize(size);
		(*components)[e.getId()] = T();

		// Set the entity's components bitmask
		e.addComponent(componentType);

		// Return the component we just added
		return getComponent<T>(e);
	}


	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e, const T& value)
	{
		T* component;

		// Get component bag
		std::vector<T>* components = getComponentBag<T>();
		ComponentType componentType = _componentTypeManager.getComponentType<T>();

		// Add the component to it
		const unsigned int size = std::max<unsigned int>(e.getId()+1, components->size());
		components->resize(size);
		(*components)[e.getId()] = T();

		// Set the entity's components bitmask
		e.addComponent(componentType);

		// Get new component
		component = getComponent<T>(e);

		// Set value
		*component = value;

		// Return the component we just added
		return component;
	}

	// Get a component from an entity
	// (returns null if entity doesn't have component of type T)
	template <typename T>
	T* ComponentManager::getComponent(EntityInfo& e)
	{
		std::vector<T>* components = getComponentBag<T>();

		// If this entity doesn't have this component return null
		if (!hasComponent<T>(e))
			return NULL;

		return &((*components)[e.getId()]);
	}

	// Get whether an entity has a component of type T
	template <typename T>
	bool ComponentManager::hasComponent(EntityInfo& e)
	{
		return e._componentMask[_componentTypeManager.getComponentType<T>()];
	}

	// Remove a component from an entity
	template <typename T>
	void ComponentManager::removeComponent(EntityInfo& e)
	{
		ComponentType componentType = _componentTypeManager.getComponentType<T>();

		e.removeComponent(componentType);
	}

	// Get a bag for a component type
	template <typename T>
	std::vector<T>* ComponentManager::getComponentBag()
	{
		std::vector<T>* components = (std::vector<T>*)_componentBags[typeid(T).name()].get();

		// If this type doesn't have a bag yet
		if (components == NULL)
		{
			// Create one
			components = new std::vector<T>();

			// Store it in hash map
			_componentBags[typeid(T).name()] = shared_ptr(components);
		}

		return components;
	}
}

#endif /* __COMPONENTMAP_H__ */
