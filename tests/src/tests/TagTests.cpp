#include "tests/TagTests.h"

#include <coment/World.h>

namespace coment
{
	namespace tests
	{
		TagTests::TagTests()
			: Test("Tag")
		{

		}

		void TagTests::run()
		{
			const char* TAG_NAME_PLAYER = "player";
			const char* TAG_NAME_ENEMY = "enemy";

			const unsigned int ENEMY_COUNT = 10;

			coment::World world;
			coment::Entity e;

			begintest("Fresh entity tag is \"\"");
				e = world.createEntity();
			endtest(world.getTag(e) == "" && world.getEntitiesByTag("").size() == 1);

			begintest("Setting entity tag name");
				world.setTag(e, TAG_NAME_PLAYER);
			endtest(world.getTag(e) == TAG_NAME_PLAYER &&
				world.getEntitiesByTag("").size() == 0 &&
				world.getEntitiesByTag(TAG_NAME_PLAYER).size() == 1);

			begintest("Removing entity removes it from tag");
				world.remove(e);
				world.loopStart();
			endtest(!world.isAlive(e) &&
				world.getEntitiesByTag("").size() == 0 &&
				world.getEntitiesByTag(TAG_NAME_PLAYER).size() == 0);

			begintest("Creating " << ENEMY_COUNT << " entities with the enemy tag and retrieving them");
				e = world.createEntity();
				world.setTag(e, TAG_NAME_PLAYER);
				for (unsigned int i = 0; i < ENEMY_COUNT; ++i)
				{
					Entity enemy = world.createEntity();
					world.setTag(enemy, TAG_NAME_ENEMY);
				}
			endtest(world.getEntitiesByTag(TAG_NAME_ENEMY).size() == ENEMY_COUNT &&
				world.getEntitiesByTag(TAG_NAME_PLAYER).size() == 1);

			return;
		}
	}
}
