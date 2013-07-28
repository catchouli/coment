#ifndef COMENT_COMPONENT_H
#define COMENT_COMPONENT_H

namespace coment
{
	// A integral type that is used to define the "type" of the component at run time
	typedef unsigned int ComponentType;

	// A struct that defines a component that can be attached to an entity
	struct Component
	{
	public:
		Component() {}
		virtual ~Component() {}

	private:
		friend class ComponentManager;
	};
}

#endif /* COMENT_COMPONENT_H */
