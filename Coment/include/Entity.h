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


		Entity(EntityId id = -1);

		EntityId _id;
	};
}

#endif /* __ENTITY_H__ */
