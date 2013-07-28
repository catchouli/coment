#ifndef COMENT_COMPONENTTYPEMANAGER_H
#define COMENT_COMPONENTTYPEMANAGER_H

#include <string>
#include <typeinfo>

#include "Manager.h"
#include "../Component.h"
#include "../utils/Map.h"

namespace coment
{
	// A map of std::type_info::name() to ComponentType ID
	typedef std::tr1::unordered_map<std::string, ComponentType> ComponentTypeMap;

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
		ComponentTypeMap::iterator it = _componentTypes.find(typeid(T).name());

		// If hash map does not contain this type
		if (it == _componentTypes.end())
		{
			// Assign it a ComponentType
			ComponentType componentType = _nextId++;

			// Add it to hash map
			_componentTypes[typeid(T).name()] = componentType;

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

#endif /* COMENT_COMPONENTTYPEMANAGER_H */
