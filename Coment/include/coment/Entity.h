#ifndef __ENTITY_H__
#define __ENTITY_H__

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

#endif /* __ENTITY_H__ */
