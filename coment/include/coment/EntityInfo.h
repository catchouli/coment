#ifndef COMENT_ENTITYINFO_H
#define COMENT_ENTITYINFO_H

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
		bool compareComponentBitmask(const BitMask& mask) const;

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
		friend class World;
		friend class EntityManager;
		friend class SystemManager;
		friend class ComponentManager;
		friend class GroupManager;

		// A protected construtor that creates an EntityInfo for a particular
		// entity id
		EntityInfo(EntityId id);

		// Which components that are attached to this entity
		BitMask _componentMask;

		// Which systems this entity belongs to
		BitMask _systemMask;

		// Which groups this entity belongs to
		BitMask _groupMask;

		// Whether or not this entity is alive
		bool _alive;

		// Whether or not this entity is waiting to be refreshed
		bool _waitingForRefresh;

		// Whether or not this entity is waiting to be removed
		bool _waitingForRemoval;

	private:
		// Whether or not this entity is valid
		bool _valid;
	};
}

#endif /* COMENT_ENTITYINFO_H */
