#include "tests/ComponentTests.h"

#include <coment/World.h>

#include "components/Position.h"
#include "components/Velocity.h"

#include "systems/MovementSystem.h"

namespace coment
{
	namespace tests
	{
		ComponentTests::ComponentTests()
			: Test("Component")
		{

		}

		void ComponentTests::run()
		{
			const int INITIAL_X = 50;
			const int INITIAL_Y = 50;

			const int INITIAL_VX = 50;
			const int INITIAL_VY = 50;

			const int WORLD_DELTA = 1;

			coment::World world;
			coment::Entity e;

			Position* pos;
			Velocity* vel;

			// Systems
			MovementSystem movementSystem;
			world.addSystem(movementSystem);

			//  Create entity
			e = world.createEntity();

			// Check entity doesn't have component before adding
			begintest("Checking entity doesn't have component yet");
			endtest(world.getComponent<Position>(e) == NULL);

			// Add component to entity
			begintest("Adding position component to entity");
				pos = world.addComponent<Position>(e);
			endtest(world.getComponent<Position>(e) != NULL);

			// Get component from entity
			begintest("Retrieve component from entity");
			endtest(world.getComponent<Position>(e) == pos);

			// Add velocity component
			begintest("Adding second component");
				vel = world.addComponent<Velocity>(e);
			endtest(vel != NULL);

			// Remove component from entity
			begintest("Remove velocity component");
				world.removeComponent<Velocity>(e);
			endtest(world.getComponent<Velocity>(e) == NULL &&
				world.getComponent<Position>(e) != NULL);

			// Remove all components from entity
			begintest("Remove all components from entity");
				world.addComponent<Velocity>(e);
				world.removeComponents(e);
			endtest(world.getComponent<Velocity>(e) == NULL &&
				world.getComponent<Position>(e) == NULL);

			// Initialise components
			pos->x = INITIAL_X;
			pos->y = INITIAL_Y;
			vel->x = INITIAL_VX;
			vel->y = INITIAL_VY;

			return;
		}
	}
}
