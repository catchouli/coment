#ifndef __ENTITYPROCESSINGSYSTEM_H__
#define __ENTITYPROCESSINGSYSTEM_H__

#include "../Entity.h"

#include "../utils/Bag.h"

#include "../systems/EntitySystem.h"

namespace coment
{
	class EntityProcessingSystem
		: public EntitySystem
	{
	public:
		EntityProcessingSystem();

		// Process a single entity, override to specify behaviour
		virtual void process(Entity e) = 0;

		// Whether to currently process this entity
		virtual bool checkProcessing();

		// Automatically call process for each entity
		void processEntities(Bag<Entity>& entities);
	};
};

#endif /* __ENTITYPROCESSINGSYSTEM_H__ */
