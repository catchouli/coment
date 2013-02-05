#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "utils/ComponentUtils.h"
#include "utils/Bag.h"

namespace coment
{
	// A struct that defines a component that can be attached to an entity
	struct Component
	{
	public:
	protected:
		Component() {};

	private:
		friend class ComponentManager;
	};
}

#endif /* __COMPONENT_H__ */
