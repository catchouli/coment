#include "coment/EntityInfo.h"

namespace coment
{
	// Constructor
	EntityInfo::EntityInfo()
		: _valid(false)
	{
	}

	// Protected Constructor
	EntityInfo::EntityInfo(EntityId id)
		: Entity(id), _valid(true)
	{
	}

	// Compare the bitmask
	bool EntityInfo::compareBitmask(const BitMask& mask) const
	{
		return (mask & _componentMask) == mask;
	}

	// Compare the system bitmask.
	bool EntityInfo::compareSystemBitmask(const BitMask& mask) const
	{
		return (mask & _systemMask) == mask;
	}

	// Add a component
	void EntityInfo::addComponent(ComponentType type)
	{
		_componentMask.setBit(type);
	}

	// Add a component
	void EntityInfo::removeComponent(ComponentType type)
	{
		_componentMask.clearBit(type);
	}
}
