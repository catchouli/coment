#ifndef COMENT_VARIABLEMANAGER_H
#define COMENT_VARIABLEMANAGER_H

#include <string>

#include "Manager.h"
#include "../utils/Map.h"
#include "../utils/SharedPtr.h"

namespace coment
{
	class World;
    
#ifdef COMENT_CONFIG_HAS_CPP11
    #define VariableMap typename std::unordered_map<std::string, T>
	typedef std::unordered_map<std::string, std::shared_ptr<void> > VariableTypeMap;
    typedef std::shared_ptr<void> shared_ptr;

#else
    #define VariableMap typename std::tr1::unordered_map<std::string, T>
	typedef std::tr1::unordered_map<std::string, std::tr1::shared_ptr<void> > VariableTypeMap;
    typedef std::tr1::shared_ptr<void> shared_ptr;

#endif

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
			_variableTypeMap[typeid(T).name()] = shared_ptr(new VariableMap());

			typeIter = _variableTypeMap.find(typeid(T).name());
		}

		return *(VariableMap*)(typeIter->second.get());
	}
}

#endif /* COMENT_VARIABLEMANAGER_H */
