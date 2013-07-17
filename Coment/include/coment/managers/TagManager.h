#ifndef __TAGMANAGER_H__
#define __TAGMANAGER_H__

#include <string>
#include <vector>

#include "Manager.h"
#include "../Entity.h"

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
		std::vector<std::string> _tagsByEntity;

		const std::vector<Entity> _emptyVector;
	};
}

#endif /* __TAGMANAGER_H__ */
