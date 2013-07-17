#include "coment/managers/TagManager.h"

#include "coment/EntityInfo.h"

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
		// Set entity's tag
		_tagsByEntity.set(e.getId(), tag);
	}

	std::string TagManager::getTag(const EntityInfo& e)
	{
		if (e.getId() < _tagsByEntity.getSize())
			return _tagsByEntity[e.getId()];

		return "";
	}
}
