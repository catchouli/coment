#include "tests/VariableTests.h"

#include <coment/World.h>

namespace coment
{
	namespace tests
	{
		VariableTests::VariableTests()
			: Test("Group")
		{

		}

		void VariableTests::run()
		{
			coment::World world;

			//world.setValue<float>("delta", 0.1f);
			//world.getValue<float>("delta");

			return;
		}
	}
}
