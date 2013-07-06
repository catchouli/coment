#ifndef __GROUPMANAGER_H__
#define __GROUPMANAGER_H__

#include <string>
#include <unordered_map>

#include "Manager.h"

#include "../Entity.h"

#include "../utils/Bag.h"

namespace coment
{
	typedef std::unordered_map<std::string, Bag<Entity> > EntityGroupMap;

	class GroupManager
		: public Manager
	{
	public:
		GroupManager();
		~GroupManager();

		void set(std::string group, Entity e);

		const Bag<Entity>& getEntities(std::string group);

		void remove(Entity e);

		std::string getGroup(Entity e);

		bool isGrouped(Entity e);

	private:
		EntityGroupMap _entitiesByGroup;
		Bag<std::string> _groupsByEntity;

		const Bag<Entity> _emptyBag;
	};
}

#endif /* __GROUPMANAGER_H__ */
