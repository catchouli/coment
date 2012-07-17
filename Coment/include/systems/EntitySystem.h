#ifndef __ENTITYSYSTEM_H__
#define __ENTITYSYSTEM_H__

#include "../Entity.h"
#include "../EntityInfo.h"
#include "../utils/BitMask.h"
#include "../utils/Bag.h"

namespace coment
{
	// Forward declaration of world
	class World;

	// A system that processes entities
	class EntitySystem
	{
	public:
		// Called by the client to initiate processing
		void update();

		// Called during initialisation of this system
		virtual void initialise();

		// Called before the processing of entities begins
		virtual void begin();

		// Called after the end of processing
		virtual void end();

		// Any implementing entity system must implement this method
		// Contains the logic to process the entities of this system
		virtual void processEntities(const Bag<Entity>& entities) = 0;

		// Returns whether this system should currently process entities
		virtual bool checkProcessing();

		// Called when an entity is added to this system
		virtual void added(Entity e);

		// Called when an entity is removed from this system
		virtual void removed(Entity e);

	protected:
		// Constructor
		EntitySystem();

		// Friends with the system manager so that it can get protected fields
		friend class SystemManager;
		
		// Add an entity
		void addEntity(EntityInfo& e);
		
		// Remove an entity
		void removeEntity(EntityInfo& e);

		// Set the world that this system belongs to
		void setWorld(World* world);

		// Register a component with this system
		template <typename T>
		void registerComponent();

		// Get the bitmask created from the combination of components
		// registered with this system
		BitMask getMask();

		// Called when an entity is refreshed
		bool refresh(const EntityInfo& e);

		// The world this system belongs to
		World* _world;

	private:
		// The bitmask to use for the entity system
		BitMask _bitmask;

		// A bag of entities that match this systems bitmask
		Bag<Entity> _entities;
	};

	// Register a component with this system
	template <typename T>
	void EntitySystem::registerComponent() 
	{
		// Generate a type id for this component if it doesn't already have one
		if (T::type < 0) 
		{
			T::type = ComponentUtils::getNextType();
		}

		// Add this component
		_bitmask.setBit(T::type);
	}
}

#endif /* __ENTITYSYSTEM_H__ */
