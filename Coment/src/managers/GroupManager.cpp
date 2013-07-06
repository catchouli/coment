#include "managers/GroupManager.h"

namespace coment
{
	GroupManager::GroupManager()
	{

	}

	GroupManager::~GroupManager()
	{

	}

	void GroupManager::set(std::string group, Entity e)
	{
		// Make sure entity only belongs to one group
		remove(e);

		// Find group in map
		EntityGroupMap::iterator it = _entitiesByGroup.find(group);

		if (it != _entitiesByGroup.end())
		{
			// Add to group
			it->second.add(e);
		}
		else
		{
			Bag<Entity> bag;

			// Insert fresh bag into map for this group
			std::pair<EntityGroupMap::iterator, bool> result = _entitiesByGroup.insert(EntityGroupMap::value_type(group, bag));

			// Add it to the new group bag
			result.first->second.add(e);
		}

		// Set entity's group
		_groupsByEntity.set(e.getId(), group);
	}

	const Bag<Entity>& GroupManager::getEntities(std::string group)
	{
		// Find group
		EntityGroupMap::iterator it = _entitiesByGroup.find(group);

		// If this group exists
		if (it != _entitiesByGroup.end())
		{
			// Get reference to entities
			Bag<Entity>& entities = _entitiesByGroup.find(group)->second;

			return entities;
		}

		return _emptyBag;
	}

	void GroupManager::remove(Entity e)
	{
		// If the entity can possibly by in a group
		if (e.getId() < _groupsByEntity.getSize())
		{
			std::string group = _groupsByEntity[e.getId()];

			// If this group exists
			if (group != "")
			{
				// Unset group
				_groupsByEntity.set(e.getId(), "");

				// Get group bag
				EntityGroupMap::iterator it =  _entitiesByGroup.find(group);
				Bag<Entity>& group = it->second;

				group.remove(e);
			}
		}
	}

	std::string GroupManager::getGroup(Entity e)
	{
		if (e.getId() < _groupsByEntity.getSize())
			return _groupsByEntity[e.getId()];
		else
			return "";
	}

	bool GroupManager::isGrouped(Entity e)
	{
		// Return false if this isn't in a group
		if (getGroup(e) == "")
			return false;
		else
			return true;
	}
}
