#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "utils/ComponentUtils.h"

namespace coment
{
	// A struct that defines a component that can be attached to an entity
	template <typename T>
	struct Component
	{
	public:
		// Get the unique id for a component type
		static ComponentType getType();

	protected:
		// Constructors
		Component();

	private:
		friend class ComponentManager;
		friend class EntitySystem;
		friend class World;
		friend class EntityManager;

		// Vars
		static ComponentType type; // The component type for this component
	};

	template <typename T>
	Component<T>::Component()
	{

	}
	
	template <typename T>
	ComponentType Component<T>::getType()
	{
		return type;
	}

	template <typename T>
	ComponentType Component<T>::type(-1);
}

#endif /* __COMPONENT_H__ */
