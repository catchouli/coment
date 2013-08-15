#include "tests/SystemTests.h"

#include <coment/World.h>

#include "components/Position.h"
#include "components/Velocity.h"

#include "systems/MovementSystem.h"

namespace coment
{
	namespace tests
	{
		SystemTests::SystemTests()
			: Test("System")
		{

		}

		void SystemTests::run()
		{
			const int INITIAL_X = 50;
			const int INITIAL_Y = 50;

			const int INITIAL_VX = 50;
			const int INITIAL_VY = 50;

			const int WORLD_DELTA = 15;

			int updates = 0;

			coment::World world;
			coment::Entity e;

			Position* pos;
			Velocity* vel;

			// Systems
			MovementSystem movementSystem;

			// Set world delta
			world.setDelta(WORLD_DELTA);

			// Check boolean event flags are set correctly
			begintest("Checking boolean flags are set to false");
			endtest(movementSystem.noEventsCalled());

			// Register system and check if registered is called
			begintest("Registering system and checking if onRegistered is called");
				world.registerSystem(movementSystem);
			endtest(movementSystem.onRegisteredCalled());

			//  Create entity
			e = world.createEntity();
			pos = world.addComponent<Position>(e);
			vel = world.addComponent<Velocity>(e);

			// Initialise components
			pos->x = INITIAL_X;
			pos->y = INITIAL_Y;
			vel->x = INITIAL_VX;
			vel->y = INITIAL_VY;

			// Run tests
			begintest("Run one update (using World::update) and check entity is updated");
				world.loopStart();
				world.update();
				updates++;
			endtest(((int)(pos->x) == INITIAL_X + INITIAL_VX * WORLD_DELTA * updates) &&
				((int)(pos->y) == INITIAL_X + INITIAL_VY * WORLD_DELTA * updates) &&
				movementSystem.onFirstUpdateCalled() &&
				movementSystem.onAddedCalled());

			begintest("Add component back and check that entity gets updated");
				updates = 0;
				pos = world.addComponent<Position>(e);
				world.loopStart();
				movementSystem.update();
				updates++;
			endtest(((int)(pos->x) == 0 + INITIAL_VX * WORLD_DELTA * updates) &&
				((int)(pos->y) == 0 + INITIAL_VY * WORLD_DELTA * updates));

			begintest("Remove all components and check that entity doesn't get updated");
				world.removeComponents(e);
				world.loopStart();
				movementSystem.update();
			endtest(((int)(pos->x) == 0 + INITIAL_VX * WORLD_DELTA * updates) &&
				((int)(pos->y) == 0 + INITIAL_VY * WORLD_DELTA * updates) &&
				movementSystem.onRemovedCalled());

			return;
		}
	}
}
