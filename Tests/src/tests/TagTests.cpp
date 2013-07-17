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
			bool success = false;
			const char* TAG_NAME = "player";

			coment::World world;
			coment::Entity e = world.createEntity();

			begintest("Uninitialised entity tag is \"\"");
			endtest(world.getTag(e) == "");

			begintest("Setting entity tag name");
				world.setTag(e, TAG_NAME);
			endtest(world.getTag(e) == TAG_NAME);

			begintest("Deleting entity and checking tag is unset");
				world.remove(e);
				world.loopStart();
			endtest(world.getTag(e) == "");

			begintest("Unsetting entity tag manually");
				world.setTag(e, TAG_NAME);
				success = (world.getTag(e) == TAG_NAME);
				world.setTag(e, "");
				success = success && (world.getTag(e) == "");
			endtest(success);

			return;
		}
	}
}
