#include "coment/Entity.h"

namespace coment
{
	Entity::Entity()
		: _id(-1)
	{

	}

	Entity::Entity(EntityId id)
		: _id(id)
	{

	}

	Entity::Entity(const EntityInfo& other)
	{
		_id = other.getId();
		_uniqueId = other.getUniqueId();
	}

	Entity& Entity::operator=(const EntityInfo& other)
	{
		_id = other.getId();
		_uniqueId = other.getUniqueId();

		return *this;
	}

	bool Entity::operator==(const Entity& other) const
	{
		return _id == other._id;
	}

	bool Entity::operator!=(const Entity& other) const
	{
		return _id != other._id;
	}

	bool Entity::isInitialised() const
	{
		if (_id == (unsigned int)-1)
			return false;

		return true;
	}

	EntityId Entity::getId() const
	{
		return _id;
	}

	EntityId Entity::getUniqueId() const
	{
		return _uniqueId;
	}
}
