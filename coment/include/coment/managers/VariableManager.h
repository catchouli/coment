#ifndef COMENT_VARIABLEMANAGER_H
#define COMENT_VARIABLEMANAGER_H

#include <string>

#include "Manager.h"
#include "../utils/Map.h"
#include "../utils/SharedPtr.h"

namespace coment
{
	class World;

	#define VariableMap typename std::tr1::unordered_map<std::string, T>
	typedef std::tr1::unordered_map<std::string, std::tr1::shared_ptr<void> > VariableTypeMap;

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
		VariableTypeMap _variableTypeMap;

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
		VariableTypeMap::iterator typeIter;

		// Find map of name to variable
		typeIter = _variableTypeMap.find(typeid(T).name());

		if (typeIter == _variableTypeMap.end())
		{
			_variableTypeMap[typeid(T).name()] = std::tr1::shared_ptr<void>(new VariableMap());

			typeIter = _variableTypeMap.find(typeid(T).name());
		}

		return *(VariableMap*)(typeIter->second.get());
	}
}

#endif /* COMENT_VARIABLEMANAGER_H */
