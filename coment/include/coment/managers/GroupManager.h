#ifndef COMENT_GROPUMANAGER_H
#define COMENT_GROPUMANAGER_H

#include "Manager.h"

namespace coment
{
	class GroupManager
		: public Manager
	{
	public:
                // Add group to entity
                void addGroup(const Entity& e, std::string group);

                // Remove group from entity
                void removeGroup(const Entity& e, std::string group);

                // Get groups by entity
                const std::vector<std::string>& getGroups(const Entity& e);

                // Get entities by group
                const std::vector<Entity>& getEntitiesByGroup(std::string group);
	};
}

#endif /* COMENT_GROPUMANAGER_H */
