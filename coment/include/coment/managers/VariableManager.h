#ifndef __VARIABLEMANAGER_H__
#define __VARIABLEMANAGER_H__

#include "Manager.h"
#include "../utils/Map.h"

namespace coment
{
	class World;

	#define VariableMap typename COMENT_MAP<std::string, T>
	#define VariableMapMap typename COMENT_MAP<World*, VariableMap >

	class VariableManager
		: public Manager
	{
	public:
		// Set a variable
		template <typename T>
		void setVariable(const std::string name, const T& value);

		// Get a value
		template <typename T>
		const T& getVariable(const std::string name);

	private:
		// Get a variable map for a specific type
		template <typename T>
		VariableMap& getVariableMap();

		// Get a variable map for a specific type
		template <typename T>
		const VariableMap& getVariableMap() const;
	};

	template <typename T>
	void VariableManager::setVariable(const std::string name, const T& value)
	{
		VariableMap& variableMap = getVariableMap<T>();
		variableMap[name] = value;
	}

	template <typename T>
	const T& VariableManager::getVariable(const std::string name)
	{
		VariableMap& variableMap = getVariableMap<T>();
		VariableMap::const_iterator it = variableMap.find(name);

		if (it == variableMap.end())
		{
			variableMap[name] = T();
			it = variableMap.find(name);
		}

		return it->second;
	}

	template <typename T>
	VariableMap& VariableManager::getVariableMap()
	{
		// A variable map for this type per world
		static VariableMapMap variableMaps;

		VariableMapMap::iterator mapIter = variableMaps.find(_world);

		if (mapIter != variableMaps.end())
		{
			variableMaps[_world] = VariableMap();

			mapIter = variableMaps.find(_world);
		}

		return mapIter->second;
	}
}

#endif /* __VARIABLEMANAGER_H__ */
