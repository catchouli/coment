#ifndef COMENT_ENTITYMANAGER_H
#define COMENT_ENTITYMANAGER_H

#include <vector>

#include "Manager.h"
#include "../Entity.h"
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

		// Called at the start of each loop and handles entity removal
		void loopStart();

		// Create an entity (will recycle dead entities ids)
		Entity createEntity();

		// Check if entity is alive
		bool isAlive(const Entity& e);

		// Get a reference to the entity info for an entity
		// (e must be a valid and living entity)
		EntityInfo& getValidEntityInfo(const Entity& e);

		// Remove an entity
		void remove(EntityInfo& e);

	protected:
		friend class World;

		// Remove an entity immediately
		void removeEntity(EntityInfo& e);

		// Get a reference to the entity info for an entity
		// (e must be a valid or previously valid entity)
		EntityInfo& getEntityInfo(const Entity& e);

	private:
		// Contains all entities
		std::vector<EntityInfo> _entityInfos;

		// Contains the entity IDs of dead or alive entities
		std::vector<Entity> _alive;
		std::vector<Entity> _dead;

		// Entities due to be removed
		std::vector<Entity> _removed;

		// Entities due to be refreshed
		std::vector<Entity> _refreshed;

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
