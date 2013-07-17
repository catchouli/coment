#ifndef __TAGMANAGER_H__
#define __TAGMANAGER_H__

#include <string>

#include "Manager.h"
#include "../Entity.h"
#include "../utils/Bag.h"

namespace coment
{
	class EntityInfo;

	class TagManager
		: public Manager
	{
	public:
		TagManager();
		~TagManager();

		void setTag(const EntityInfo& e, std::string tag);

		std::string getTag(const EntityInfo& e);

	private:
		Bag<std::string> _tagsByEntity;

		const Bag<Entity> _emptyBag;
	};
}

#endif /* __TAGMANAGER_H__ */
