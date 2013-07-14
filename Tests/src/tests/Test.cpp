#include "tests/Test.h"

namespace coment
{
	namespace tests
	{
		Test::Test(std::string name)
			: testsRun(0), testsSucceeded(0)
		{
			this->name = name;
		}

		Test::~Test()
		{

		}

		std::string Test::getName()
		{
			return name;
		}

		int Test::getTestsRun()
		{
			return testsRun;
		}

		int Test::getTestsSucceeded()
		{
			return testsSucceeded;
		}
	}
}
