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
			// Coment world
			coment::World world;

			// Systems
			MovementSystem movementSystem;

			begintest("Test tests system (success)");
			endtest(true);

			begintest("Test tests system (failure)")
			endtest(false);

			return;
		}
	}
}
