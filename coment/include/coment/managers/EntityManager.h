#ifndef COMENT_ENTITYMANAGER_H
#define COMENT_ENTITYMANAGER_H

#include <vector>

#include "Manager.h"
#include "../EntityInfo.h"

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

		// Check if entity is alive
		bool isAlive(const Entity& e);

		// Get a reference to the entity info for an entity
		EntityInfo& getEntityInfo(const Entity& e);

	protected:
		friend class World;

		// Remove an entity from the manager
		void removeEntity(EntityInfo& e);

	private:
		// Contains all entities
		std::vector<EntityInfo> _entityInfos;

		// Contains the entity IDs of dead or alive entities
		std::vector<Entity> _alive;
		std::vector<Entity> _dead;

		// How many entities are in the manager
		int _count;

		// The next valid entity IDs
		EntityId _nextEntityId;
		EntityId _nextUniqueEntityId;

		// The total amount of removed and added entities
		int _totalCreated;
		int _totalRemoved;
	};
}

#endif /* COMENT_ENTITYMANAGER_H */
