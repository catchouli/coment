#include <iostream>
#include <vector>
#include <exception>
#include <cassert>

#include "tests/Test.h"
#include "tests/ComponentTests.h"

using namespace coment::tests;

int main(int argc, char** argv)
{
	// Run tests
	std::vector<Test*> tests;

	// Create tests
	tests.push_back(new ComponentTests());

	// Run all tests
	int failed = 0;
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		Test* test = *it;

		std::cout << "Running " << test->getName() << " tests." << std::endl;

		// Run test
		test->run();

		std::cout << "Finished running " << test->getTestsRun() << " tests, "
			<< test->getTestsSucceeded() << " succeeded";

		// Update failed
		failed += (test->getTestsRun() - test->getTestsSucceeded());
	}

	// If any tests failed
	if (failed > 0)
	{
		std::cout << ", " << failed << " tests failed" << std::endl;
	}

	// Clean up memory
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		delete *it;
	}

	return 0;
}
