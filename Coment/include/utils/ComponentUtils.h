#ifndef __COMPONENTUTILS_H__
#define __COMPONENTUTILS_H__

namespace coment
{
	// A integral type that is used to define the "type" of the component at run time
	typedef int ComponentType;

	// A utils class that allows us to get ids for components
	struct ComponentUtils 
	{
	private:
		// Add some friends
		friend class ComponentTypeManager;

		// Get the next valid id for a component
		static ComponentType getNextType();
		static ComponentType nextId;
	};
}

#endif /* __COMPONENTUTILS_H__ */
