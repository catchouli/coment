#include "coment/managers/TagManager.h"

#include "coment/EntityInfo.h"
#include "coment/utils/Functions.h"

namespace coment
{
	TagManager::TagManager()
	{

	}

	TagManager::~TagManager()
	{

	}

	void TagManager::setTag(const EntityInfo& e, std::string tag)
	{
		_tagsByEntity.resize(e.getId()+1);

		// Get old tag
		std::string oldTag = _tagsByEntity[e.getId()];

		std::vector<Entity>& oldTagEntities = _entityArraysByTag[oldTag];
		std::vector<Entity>& newTagEntities = _entityArraysByTag[tag];

		// Set entity's tag
		_tagsByEntity[e.getId()] = tag;

		// Remove entity from old tag collection
		removeFirst(oldTagEntities, (Entity)e);

		// Add entity to new tag collection
		newTagEntities.push_back(e);
	}

	std::string TagManager::getTag(const EntityInfo& e)
	{
		if (e.getId() < _tagsByEntity.size())
			return _tagsByEntity[e.getId()];

		return "";
	}

	const std::vector<Entity>& TagManager::getEntities(std::string tag)
	{
		return _entityArraysByTag[tag];
	}

	void TagManager::removeEntity(const EntityInfo& e)
	{
		std::string tag = _tagsByEntity[e.getId()];
		std::vector<Entity>& entities = _entityArraysByTag[tag];

		removeFirst(entities, (Entity)e);

		_tagsByEntity[e.getId()] = "";
	}
}
