#ifndef __VARIABLEMANAGER_H__
#define __VARIABLEMANAGER_H__

#include <string>

#include "Manager.h"
#include "../utils/Map.h"
#include "../utils/SharedPtr.h"

namespace coment
{
	class World;

	#define VariableMap typename std::tr1::unordered_map<std::string, T>
	typedef std::tr1::unordered_map<std::string, std::tr1::shared_ptr<void> > TypeToVariableMapMap;
	typedef std::tr1::unordered_map<World*, TypeToVariableMapMap > WorldToTypeMapMap;

	class VariableManager
		: public Manager
	{
	public:
		// Set a variable
		template <typename T>
		void setValue(const std::string name, const T& value);

		// Get a value
		template <typename T>
		const T& getValue(const std::string name);

	private:
		WorldToTypeMapMap _WorldToTypeMapMap;

		// Get a variable map for a specific type
		template <typename T>
		VariableMap& getValueMap();
	};

	template <typename T>
	void VariableManager::setValue(const std::string name, const T& value)
	{
		VariableMap& variableMap = getValueMap<T>();
		variableMap[name] = value;
	}

	template <typename T>
	const T& VariableManager::getValue(const std::string name)
	{
		VariableMap& variableMap = getValueMap<T>();
		VariableMap::const_iterator it = variableMap.find(name);

		if (it == variableMap.end())
		{
			variableMap[name] = T();
			it = variableMap.find(name);
		}

		return it->second;
	}

	template <typename T>
	VariableMap& VariableManager::getValueMap()
	{
		WorldToTypeMapMap::iterator worldIter;
		TypeToVariableMapMap::iterator typeIter;

		// Find map of types to variable maps
		worldIter = _WorldToTypeMapMap.find(_world);

		if (worldIter == _WorldToTypeMapMap.end())
		{
			_WorldToTypeMapMap[_world] = TypeToVariableMapMap();

			worldIter = _WorldToTypeMapMap.find(_world);
		}

		// Find map of name to variable
		typeIter = worldIter->second.find(typeid(T).name());

		if (typeIter == worldIter->second.end())
		{
			worldIter->second[typeid(T).name()] = std::tr1::shared_ptr<void>(new VariableMap());

			typeIter = worldIter->second.find(typeid(T).name());
		}

		return *(VariableMap*)(typeIter->second.get());

		/*VariableMapMap::iterator mapIter = variableMaps.find(_world);

		if (mapIter != variableMaps.end())
		{
			variableMaps[_world] = std::tr1::shared_ptr<void>(new VariableMap());

			mapIter = variableMaps.find(_world);
		}

		return *(VariableMap*)(mapIter->second.get());*/
	}
}

#endif /* __VARIABLEMANAGER_H__ */
