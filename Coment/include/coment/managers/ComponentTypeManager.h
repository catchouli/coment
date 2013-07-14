#ifndef __COMPONENTTYPEMANAGER_H__
#define __COMPONENTTYPEMANAGER_H__

#include <typeinfo>
#include <unordered_map>

#include "Manager.h"
#include "../Component.h"

namespace coment
{
	// A map of std::type_info hash to ComponentType ID
	typedef std::unordered_map<size_t, ComponentType> ComponentTypeMap;

	class ComponentTypeManager
		: public Manager
	{
	public:
		ComponentTypeManager() : _nextId(0) {}

		template <typename T>
		ComponentType getComponentType();

	private:
		ComponentTypeMap _componentTypes;

		ComponentType _nextId;
	};

	template <typename T>
	ComponentType ComponentTypeManager::getComponentType()
	{
		size_t hash_code = typeid(T).hash_code();
		ComponentTypeMap::iterator it = _componentTypes.find(hash_code);

		// If hash map does not contain this type
		if (it == _componentTypes.end())
		{
			// Assign it a ComponentType
			ComponentType componentType = _nextId++;

			// Add it to hash map
			_componentTypes[typeid(T).hash_code()] = componentType;

			// Return it
			return componentType;
		}
		else
		{
			// Return component type
			return (*it).second;
		}
	}
}

#endif /* __COMPONENTTYPEMANAGER_H__ */
