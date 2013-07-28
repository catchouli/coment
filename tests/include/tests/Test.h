#ifndef COMENT_TESTS_TEST_H
#define COMENT_TESTS_TEST_H

#include <string>
#include <iostream>
#include <iomanip>

#include "TestMacros.h"

namespace coment
{
	namespace tests
	{
		class Test
		{
		public:
			Test(std::string name);
			virtual ~Test();

			// Run all tests
			virtual void run() = 0;

			// Get name of test set
			virtual std::string getName();

			// Get test statistics
			int getTestsRun();
			int getTestsSucceeded();

		protected:
			std::string name;

			int testsRun;
			int testsSucceeded;
		};
	}
}

#endif /* COMENT_TESTS_TEST_H */
