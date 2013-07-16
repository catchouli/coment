#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <tr1/unordered_map>

#include "Manager.h"
#include "../Component.h"
#include "../utils/Bag.h"
#include "../exceptions/CompMapUnregistered.h"
#include "../utils/HashGenerator.h"

namespace coment
{
	typedef std::tr1::unordered_map<size_t, void*> ComponentBagMap;

	// The component manager keeps track of which components are attached to which entities
	class ComponentManager
		: public Manager
	{
	public:
		ComponentManager();
		~ComponentManager();

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
		Bag<T>* getComponentBag();

	private:
		// Manager for component types
		ComponentTypeManager* _componentTypeManager;

		// A map of component bags
		ComponentBagMap _componentBags;
	};

	// Add a component to an entity
	template <typename T>
	T* ComponentManager::addComponent(EntityInfo& e)
	{
		Bag<T>* components = getComponentBag<T>();
		ComponentType componentType = _componentTypeManager->getComponentType<T>();

		// Add the component to it
		components->set(e.getId(), T());

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
		Bag<T>* components = getComponentBag<T>();

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
		e._systemMask.clear(T::type);
	}

	// Get a bag for a component type
	template <typename T>
	Bag<T>* ComponentManager::getComponentBag()
	{
		size_t hash_code = HashGenerator::hash<T>();
		Bag<T>* components = (Bag<T>*)_componentBags[hash_code];

		// If this type doesn't have a bag yet
		if (components == nullptr)
		{
			// Create one
			components = new Bag<T>();

			// Store it in hash map
			_componentBags[hash_code] = components;
		}

		return components;
	}
}

#endif /* __COMPONENTMAP_H__ */
