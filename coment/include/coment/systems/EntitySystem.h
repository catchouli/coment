#ifndef __ENTITYSYSTEM_H__
#define __ENTITYSYSTEM_H__

#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "../Entity.h"
#include "../EntityInfo.h"
#include "../utils/BitMask.h"
#include "../managers/ComponentTypeManager.h"

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

		// Enable processing of this system
		void setEnabled(bool enabled);

		// Get whether this system is enabled
		bool getEnabled();

		// Called during initialisation of this system
		virtual void initialise();

		// Called before the processing of entities begins
		virtual void begin();

		// Called after the end of processing
		virtual void end();

		// Any implementing entity system must implement this method
		// Contains the logic to process the entities of this system
		virtual void processEntities(std::vector<Entity>& entities) = 0;

		// Returns whether this system should currently process entities
		virtual bool checkProcessing();

		// Called when an entity is added to this system
		virtual void added(const Entity& e);

		// Called when an entity is removed from this system
		virtual void removed(const Entity& e);

	protected:
		// Constructor
		EntitySystem();

		// Friends with the system manager so that it can get protected fields
		friend class SystemManager;

		// Indicates that this system has been registered with the world
		virtual void onRegistered();

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
		BitMask getComponentMask();

		// Called when an entity is refreshed
		bool refresh(const EntityInfo& e);

		// The world this system belongs to
		World* _world;

	private:
		ComponentTypeManager* getComponentTypeManager();

		// A pointer to the world's component type manager
		ComponentTypeManager* _componentTypeManager;

		// Whether to process this system
		bool _enabled;

		// The bitmask to use for the entity system
		BitMask _bitmask;

		// A bag of entities that match this systems bitmask
		std::vector<Entity> _entities;
	};

	// Register a component with this system
	template <typename T>
	void EntitySystem::registerComponent()
	{
		if (_world == NULL)
		{
			fprintf(stderr, "Error: attempting to register component before being added to the world.");
			exit(1);
		}
		else if (_componentTypeManager == NULL)
		{
			_componentTypeManager = getComponentTypeManager();
		}

		// Add this component
		_bitmask.setBit(_componentTypeManager->getComponentType<T>());
	}
}

#endif /* __ENTITYSYSTEM_H__ */
