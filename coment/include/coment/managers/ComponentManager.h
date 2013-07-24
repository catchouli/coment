#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <string>
#include <vector>

#include "Manager.h"
#include "../Component.h"
#include "../utils/Map.h"
#include "../utils/SharedPtr.h"
#include "../exceptions/CompMapUnregistered.h"

namespace coment
{
	typedef std::tr1::unordered_map<std::string, std::tr1::shared_ptr<void> > ComponentBagMap;

	// The component manager keeps track of which components are attached to which entities
	class ComponentManager
		: public Manager
	{
	public:
		ComponentManager();

		// Add a component onto an entity
		template <typename T>
		T* addComponent(EntityInfo& e);

		// Get a component from an entity
		template <typename T>
		T* getComponent(EntityInfo& e);

		// Check if entity has component
		template <typename T>
		bool hasComponent(EntityInfo& e);

		// Initialise this manager once it's registered with the world
		virtual void onRegistered();

		// Remove a component from an entity
		template <typename T>
		void removeComponent(EntityInfo& e);

		// Remove all the components from an entity
		void removeComponents(EntityInfo& e);

	protected:
		// Get a bag for a component type
		template <typename T>
		std::vector<T>* getComponentBag();

	private:
		// Private copy constructor/assignment operator (no copying)
		ComponentManager(const ComponentManager&);
		const ComponentManager& operator=(const ComponentManager&);

		// Manager for component types
		ComponentTypeManager* _componentTypeManager;

		// A map of component bags
		ComponentBagMap _componentBags;
	};

	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e)
	{
		std::vector<T>* components = getComponentBag<T>();
		ComponentType componentType = _componentTypeManager->getComponentType<T>();

		// Add the component to it
		components->resize(e.getId()+1);
		(*components)[e.getId()] = T();

		// Set the entity's components bitmask
		e.addComponent(componentType);

		// Return the component we just added
		return getComponent<T>(e);
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
		return e._componentMask[_componentTypeManager->getComponentType<T>()];
	}

	// Remove a component from an entity
	template <typename T>
	void ComponentManager::removeComponent(EntityInfo& e)
	{
		ComponentType componentType = _componentTypeManager->getComponentType<T>();

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
			_componentBags[typeid(T).name()] = std::tr1::shared_ptr<void>(components);
		}

		return components;
	}
}

#endif /* __COMPONENTMAP_H__ */
