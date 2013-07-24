#include "tests/VariableTests.h"

#include <coment/World.h>

namespace coment
{
	namespace tests
	{
		VariableTests::VariableTests()
			: Test("Variable")
		{

		}

		void VariableTests::run()
		{
			coment::World world;

			world.getManager<VariableManager>()->setVariable<float>("delta", 0.1f);
			std::cout << world.getManager<VariableManager>()->getVariable<float>("delta") << std::endl;

			return;
		}
	}
}
