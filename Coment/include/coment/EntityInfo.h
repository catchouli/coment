#ifndef __ENTITYINFO_H__
#define __ENTITYINFO_H__

#include "Entity.h"
#include "Component.h"
#include "utils/Bitset.h"
#include "utils/BitMask.h"

namespace coment
{
	// The internal representation of an entity
	class EntityInfo
		: public Entity
	{
	public:
		// Constructor
		EntityInfo();

		// Compare the bitmask
		bool compareBitmask(const BitMask& mask) const;

		// Compare the system bitmask
		bool compareSystemBitmask(const BitMask& mask) const;

		// Add a component to this entity
		void addComponent(ComponentType type);

		// Remove a component to this entity
		void removeComponent(ComponentType type);

		// Remove all components to this entity
		void removeComponents();

	protected:
		// We are friends with the entity manager so that it can call
		// this protected constructor
		friend class EntityManager;
		friend class SystemManager;
		friend class ComponentManager;

		// A protected construtor that creates an EntityInfo for a particular
		// entity id
		EntityInfo(EntityId id);

		// Which components that are attached to this entity
		BitMask _componentMask;

		// System bitmask
		BitMask _systemMask;

		// Whether or not this entity is alive
		bool _alive;

	private:
		// Whether or not this entity is valid
		bool _valid;
	};
}

#endif /* __ENTITYINFO_H__ */
