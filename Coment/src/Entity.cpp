#include "Entity.h"

namespace coment
{
	Entity::Entity(EntityId id)
		: _id(id)
	{

	}

	bool Entity::operator==(const Entity& other) const
	{
		return _id == other._id;
	}

	bool Entity::operator!=(const Entity& other) const
	{
		return _id != other._id;
	}

	EntityId Entity::getId()
	{
		return _id;
	}
}
