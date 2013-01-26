#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "utils/ComponentUtils.h"
#include "utils/Bag.h"

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
		// TODO: does this need all of these?
		friend class ComponentManager;
		friend class EntitySystem;
		friend class World;
		friend class EntityManager;

		// Vars
		static ComponentType type; // The component type for this component

		// A bag containing all of the components of this type
		static Bag<T> components;
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

	template <typename T>
	Bag<T> Component<T>::components;
}

#endif /* __COMPONENT_H__ */
