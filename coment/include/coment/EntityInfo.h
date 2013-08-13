#ifndef COMENT_ENTITYINFO_H
#define COMENT_ENTITYINFO_H

#include "Component.h"
#include "EntityId.h"
#include "utils/BitMask.h"

namespace coment
{
	// The internal representation of an entity
	class EntityInfo
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

		// Get IDs of entity
		EntityId getId() const;
		EntityId getUniqueId() const;

	protected:
		// World is friend so it can instantiate this class
		// (the default constructor creates an "uninitialised" version)
		friend class World;

		// Managers are friends so they can access and modify the entity's masks
		friend class EntityManager;
		friend class SystemManager;
		friend class ComponentManager;
		friend class GroupManager;

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

		// The entity ID
		EntityId _id;

		// The unique entity ID
		EntityId _uniqueId;
	};
}

#endif /* COMENT_ENTITYINFO_H */
