#ifndef COMENT_ENTITY_H
#define COMENT_ENTITY_H

namespace coment
{
	typedef unsigned int EntityId;

	class Entity
	{
	public:
		Entity();

		bool isInitialised() const;

		EntityId getId() const;

		EntityId getUniqueId() const;

		bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

	protected:
		friend class EntityManager;

		Entity(EntityId id);

		EntityId _id;
		EntityId _uniqueId;
	};
}

#endif /* COMENT_ENTITY_H */
