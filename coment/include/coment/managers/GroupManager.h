#ifndef COMENT_GROUPMANAGER_H
#define COMENT_GROUPMANAGER_H

#include <vector>
#include <string>

#include "Manager.h"
#include "../Entity.h"
#include "../EntityInfo.h"
#include "../utils/Map.h"

namespace coment
{
	typedef std::tr1::unordered_map<std::string, int> GroupIDMask;

	class GroupManager
		: public Manager
	{
	public:
		GroupManager();

		// Add entity to group
                void addGroup(EntityInfo& e, std::string group);

		// Remove entity from group
                void removeGroup(EntityInfo& e, std::string group);

		// Remove entity from all groups
		void removeGroups(EntityInfo& e);

                // Get whether entity is in group
		bool isInGroup(const EntityInfo& e, std::string group);

                // Get entities by group
                const std::vector<Entity>& getEntitiesByGroup(std::string group);

	protected:
		int getGroupID(std::string group);

	private:
		GroupIDMask _groupIDs;
		std::vector<std::vector<Entity> > _entitiesByGroup;

		int _nextGroupID;
	};
}

#endif /* COMENT_GROUPMANAGER_H */
