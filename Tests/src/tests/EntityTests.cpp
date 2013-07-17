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

			begintest("Checking system recognises uninitialised entity")
			endtest(!e.isInitialised());

			begintest("Creating entity");
				e = world.createEntity();
			endtest(e.isInitialised());

			//begintest("Adding position Entity to entity");
			//world.addEntity<Position>(e);
			//endtest(world.getManager<EntityManager>()->hasEntity<Position>(world.getManager<EntityManager>()->getEntityInfo(e)));

			return;
		}
	}
}
