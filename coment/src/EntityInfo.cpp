#include "coment/EntityInfo.h"

namespace coment
{
	EntityInfo::EntityInfo()
		: _alive(false), _waitingForRefresh(false), _waitingForRemoval(false), _valid(false)
	{

	}

	// Compare the bitmask
	bool EntityInfo::compareComponentBitmask(const BitMask& mask) const
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

	// Remove a component
	void EntityInfo::removeComponent(ComponentType type)
	{
		_componentMask.clearBit(type);
	}

	// Remove all components
	void EntityInfo::removeComponents()
	{
		_componentMask.clear();
	}

	EntityId EntityInfo::getId() const
	{
		return _id;
	}

	EntityId EntityInfo::getUniqueId() const
	{
		return _uniqueId;
	}
}
