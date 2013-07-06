#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "../Component.h"
#include "../EntityInfo.h"

#include "utils/Bag.h"

#include "managers/Manager.h"

namespace coment
{
	class World;

	// A class that manages all of the entities in a world
	class EntityManager
		: public Manager
	{
	public:
		// Constructors
		EntityManager();
		~EntityManager();

		// Create an entity (will recycle dead entities ids)
		Entity createEntity();

	protected:
		friend class World;

		// Remove an entity from the manager
		void removeEntity(EntityInfo& e);

		// Get a reference to the entity info for an entity
		EntityInfo& getEntityInfo(Entity e);

		// Add a component to an entity
		template <typename T>
		void addComponent(Entity e, T c);

	private:
		// Contains all entities
		Bag<EntityInfo> _entities;

		// Contains the entity IDs of dead or alive entities
		Bag<Entity> _alive;
		Bag<Entity> _dead;

		// How many entities are in the manager
		int _count;
		EntityId _nextEntityId; // The next valid entity id

		// The total amount of removed and added entities
		int _totalCreated;
		int _totalRemoved;
	};

	// Add a component to an entity
	template <typename T>
	void EntityManager::addComponent(Entity e, T c)
	{
		_entities.get(e.getId()).addComponent(T::type);
	}
}

#endif /* __ENTITYMANAGER_H__ */
