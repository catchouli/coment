#include "coment/managers/GroupManager.h"

#include "coment/utils/Functions.h"

namespace coment
{
	GroupManager::GroupManager()
		: _nextGroupID(0)
	{

	}

	// Add entity to group
	void GroupManager::addGroup(EntityInfo& e, std::string group)
	{
		// Get group ID
		int groupID = getGroupID(group);

		// Get group bitmask
		BitMask groupMask;
		groupMask.setBit(groupID);

		// If entity not already in group
		if ((e._groupMask & groupMask).isZero())
		{
			// Get group
			std::vector<Entity>& group = _entitiesByGroup[groupID];

			// Add entity
			group.push_back((Entity)e);

			// Update group bitmask
			e._groupMask.setBit(groupID);
		}
	}

	// Remove entity from group
	void GroupManager::removeGroup(EntityInfo& e, std::string group)
	{
		// Get group ID
		int groupID = getGroupID(group);

		// Get group bitmask
		BitMask groupMask;
		groupMask.setBit(groupID);

		// If entity is in group
		if (!(e._groupMask & groupMask).isZero())
		{
			// Get group
			std::vector<Entity>& group = _entitiesByGroup[groupID];

			// Remove entity
			removeFirst(group, (Entity)e);

			// Update group bitmask
			e._groupMask.clearBit(groupID);
		}
	}

	// Remove entity from all groups
	void GroupManager::removeGroups(EntityInfo& e)
	{
		// Iterate through group IDs
		for (int i = 0; i < _nextGroupID; ++i)
		{
			// If entity is in group
			if (e._groupMask[i])
			{
				// Get group
				std::vector<Entity>& group = _entitiesByGroup[i];

				// Remove entity
				removeFirst(group, (Entity)e);
			}
		}

		// Clear group bitmask
		e._groupMask.clear();
	}

	// Get whether entity is in group
	bool GroupManager::isInGroup(const EntityInfo& e, std::string group)
	{
		// Get group ID
		int groupID = getGroupID(group);

		return e._groupMask[groupID];
	}

	// Get entities by group
	const std::vector<Entity>& GroupManager::getEntitiesByGroup(std::string group)
	{
		// Get group ID
		int groupID = getGroupID(group);

		return _entitiesByGroup[groupID];
	}

	// Get the assigned ID of a group
	int GroupManager::getGroupID(std::string group)
	{
		int groupID;

		// Check if map contains group
		GroupIDMask::const_iterator it = _groupIDs.find(group);

		// If map doesn't contain group
		if (it == _groupIDs.end())
		{
			// Assign group an ID
			groupID = _nextGroupID++;

			// Extend groups vector
			const unsigned int size = std::max(groupID+1, (int)_entitiesByGroup.size());
			_entitiesByGroup.resize(size);

			// Set value in map
			_groupIDs[group] = groupID;
		}
		// If map does contain group
		else
		{
			// Get ID
			groupID = it->second;
		}

		return groupID;
	}
}
