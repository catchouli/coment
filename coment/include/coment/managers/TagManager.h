#ifndef COMENT_TAGMANAGER_H
#define COMENT_TAGMANAGER_H

#include <string>
#include <vector>

#include "Manager.h"
#include "../Entity.h"
#include "../utils/Map.h"

namespace coment
{
	typedef std::tr1::unordered_map<std::string, std::vector<Entity> > EntityArrayMap;

	class EntityInfo;

	class TagManager
		: public Manager
	{
	public:
		TagManager();
		~TagManager();

		void setTag(const EntityInfo& e, std::string tag);

		std::string getTag(const EntityInfo& e);

		const std::vector<Entity>& getEntities(std::string tag);

		void removeEntity(const EntityInfo& e);

	private:
		std::vector<std::string> _tagsByEntity;
		EntityArrayMap _entityArraysByTag;

		const std::vector<Entity> _emptyVector;
	};
}

#endif /* COMENT_TAGMANAGER_H */
