#ifndef COMENT_ENTITYPROCESSINGSYSTEM_H
#define COMENT_ENTITYPROCESSINGSYSTEM_H

#include <vector>

#include "../Entity.h"
#include "../systems/EntitySystem.h"

namespace coment
{
	class EntityProcessingSystem
		: public EntitySystem
	{
	public:
		EntityProcessingSystem();

		// Process a single entity, override to specify behaviour
		virtual void process(const Entity& e) = 0;

		// Whether to currently process this entity
		virtual bool checkProcessing();

		// Automatically call process for each entity
		void processEntities(std::vector<Entity>& entities);

	protected:
		/* Events */
		// Indicates that this system has been registered with the world
/*		virtual void onRegistered();

		// Called before the first update of this system
		virtual void onFirstUpdate();

		// Called before the processing of entities begins
		virtual void onBegin();

		// Called after the end of processing
		virtual void onEnd();

		// Called when an entity is added to this system
		virtual void onAdded(const Entity& e);

		// Called when an entity is removed from this system
		virtual void onRemoved(const Entity& e);
*/	};
};

#endif /* COMENT_ENTITYPROCESSINGSYSTEM_H */
