#ifndef COMENT_ENTITY_H
#define COMENT_ENTITY_H

#include "Component.h"
#include "EntityId.h"
#include "EntityInfo.h"

namespace coment
{
	class Entity
	{
	public:
		Entity();
		Entity(const EntityInfo& info);

		Entity& operator=(const EntityInfo& other);

		bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

		bool isInitialised() const;

		EntityId getId() const;
		EntityId getUniqueId() const;

	protected:
		friend class EntityManager;

		Entity(EntityId id);

	private:
		EntityId _id;
		EntityId _uniqueId;
	};
}

#endif /* COMENT_ENTITY_H */
