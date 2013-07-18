#include "tests/EntityTests.h"

#include <coment/World.h>

namespace coment
{
	namespace tests
	{
		EntityTests::EntityTests()
			: Test("Entity")
		{

		}

		void EntityTests::run()
		{
			coment::World world;
			coment::Entity e;

			begintest("Checking system recognises uninitialised entity");
			endtest(!e.isInitialised());

			begintest("Creating entity");
				e = world.createEntity();
			endtest(e.isInitialised() && world.isAlive(e));

			begintest("Removing entity and checking if it's alive");
				world.remove(e);
				world.loopStart();
			endtest(!world.isAlive(e));

			return;
		}
	}
}
