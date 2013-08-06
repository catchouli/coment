#include "tests/GroupTests.h"

#include <coment/World.h>

namespace coment
{
	namespace tests
	{
		GroupTests::GroupTests()
			: Test("Group")
		{

		}

		void GroupTests::run()
		{
			const char* TEST_GROUP_1 = "Players";
			const char* TEST_GROUP_2 = "Enemies";

			coment::World world;
			coment::Entity e1 = world.createEntity();
			coment::Entity e2 = world.createEntity();
			coment::Entity e3 = world.createEntity();

			begintest("Check entity isn't in any groups");
			endtest(!world.isInGroup(e1, TEST_GROUP_1) &&
				!world.isInGroup(e1, TEST_GROUP_2));

			begintest("Add entity to " << TEST_GROUP_1 << " group");
				world.addGroup(e1, TEST_GROUP_1);
			endtest( world.isInGroup(e1, TEST_GROUP_1) &&
				!world.isInGroup(e1, TEST_GROUP_2));

			begintest("Add entity to " << TEST_GROUP_2 << " group only");
				world.removeGroup(e1, TEST_GROUP_1);
				world.addGroup(e1, TEST_GROUP_2);
			endtest(!world.isInGroup(e1, TEST_GROUP_1) &&
				 world.isInGroup(e1, TEST_GROUP_2));

			begintest("Add entity to both groups");
				world.addGroup(e1, TEST_GROUP_1);
			endtest( world.isInGroup(e1, TEST_GROUP_1) &&
				 world.isInGroup(e1, TEST_GROUP_2));

			begintest("Remove entity from all groups");
				world.removeGroups(e1);
			endtest(!world.isInGroup(e1, TEST_GROUP_1) &&
				!world.isInGroup(e1, TEST_GROUP_2));

			begintest("Add multiple entities to " << TEST_GROUP_2 << " group");
				world.addGroup(e1, TEST_GROUP_1);
				world.addGroup(e1, TEST_GROUP_2);
				world.addGroup(e2, TEST_GROUP_2);
			endtest(world.getEntitiesByGroup(TEST_GROUP_1).size() == 1 &&
				world.getEntitiesByGroup(TEST_GROUP_2).size() == 2);

			begintest("Add multiple entities to " << TEST_GROUP_1 << " group");
				world.addGroup(e2, TEST_GROUP_1);
				world.addGroup(e3, TEST_GROUP_1);
			endtest(world.getEntitiesByGroup(TEST_GROUP_1).size() == 3 &&
				world.getEntitiesByGroup(TEST_GROUP_2).size() == 2);

			return;
		}
	}
}
