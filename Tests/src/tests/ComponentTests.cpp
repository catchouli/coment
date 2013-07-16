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
			coment::World world;
			coment::Entity e;

			// Systems
			MovementSystem movementSystem;
			world.addSystem(movementSystem);

			//  Create entity
			world.createEntity();

			// Add component to entity
			begintest("Adding position component to entity");
			world.addComponent<Position>(e);
			endtest(world.getManager<ComponentManager>()->hasComponent<Position>(world.getManager<EntityManager>()->getEntityInfo(e)));
			return;
		}
	}
}
