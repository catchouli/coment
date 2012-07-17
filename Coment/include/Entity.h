#ifndef __ENTITY_H__
#define __ENTITY_H__

namespace coment
{	
	typedef unsigned int EntityId;

	class Entity
	{
	public:
		EntityId getId();
		
		bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

	protected:
		friend class EntityManager;
		template <typename> friend class Bag;

		Entity(EntityId id = -1);

	private:
		EntityId _id;
	};
}

#endif /* __ENTITY_H__ */
