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

			bool success = false;
			int updates = 0;

			coment::World world;
			coment::Entity e;

			Position* pos;
			Velocity* vel;

			// Systems
			MovementSystem movementSystem;

			// Register system and check if onRegistered is called
			begintest("Registering system and checking if onRegistered is called");
				success = !movementSystem.isRegistered();
				world.addSystem(movementSystem);
				success = success && movementSystem.isRegistered();
			endtest(success);

			//  Create entity
			e = world.createEntity();
			pos = world.addComponent<Position>(e);
			vel = world.addComponent<Velocity>(e);
			world.refresh(e);

			// Initialise components
			pos->x = INITIAL_X;
			pos->y = INITIAL_Y;
			vel->x = INITIAL_VX;
			vel->y = INITIAL_VY;

			// Run one update and check that the position and velocity are correct
			begintest("Run one update (using World::update) and check entity is updated");
			world.setDelta(WORLD_DELTA);
			world.loopStart();
			world.update();
			updates++;
			endtest(((int)(pos->x) == INITIAL_X + INITIAL_VX * WORLD_DELTA * updates) &&
				((int)(pos->y) == INITIAL_Y + INITIAL_VY * WORLD_DELTA * updates));

			// Run one update and check that the position and velocity are correct
			begintest("Run one update (using system::update) and check entity is updated");
			world.setDelta(WORLD_DELTA);
			world.loopStart();
			movementSystem.update();
			updates++;
			endtest(((int)(pos->x) == INITIAL_X + INITIAL_VX * WORLD_DELTA * updates) &&
				((int)(pos->y) == INITIAL_Y + INITIAL_VY * WORLD_DELTA * updates));

			return;
		}
	}
}
