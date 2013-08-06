#include <iostream>
#include <vector>
#include <exception>
#include <cassert>

#include "tests/Test.h"
#include "tests/EntityTests.h"
#include "tests/ComponentTests.h"
#include "tests/SystemTests.h"
#include "tests/TagTests.h"
#include "tests/GroupTests.h"
#include "tests/VariableTests.h"
#include "tests/UtilsTests.h"

using namespace coment::tests;

int main(int argc, char** argv)
{
	int failed = 0;
	int succeeded = 0;

	// Run tests
	std::vector<Test*> tests;

	// Create tests
	tests.push_back(new EntityTests());
	tests.push_back(new ComponentTests());
	tests.push_back(new SystemTests());
	tests.push_back(new TagTests());
	tests.push_back(new GroupTests());
	tests.push_back(new VariableTests());
	tests.push_back(new UtilsTests());

	// Run all tests
	std::cout << "Running all tests" << std::endl;
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		Test* test = *it;
		int failedCurrent = 0;

		std::cout << " Running " << test->getName() << " tests." << std::endl;

		// Run test
		test->run();

		failedCurrent = test->getTestsRun() - test->getTestsSucceeded();

		std::cout << " Finished running " << test->getTestsRun() << " tests, "
			<< test->getTestsSucceeded() << " succeeded, " << failedCurrent << " failed" << std::endl;

		// Update failed
		succeeded += test->getTestsSucceeded();
		failed += failedCurrent;
	}

	// Overall
	std::cout << "Overall: " << succeeded << " test" << (succeeded > 1 ? "s" : "") << " succeeded";

	// If any tests failed
	if (failed > 0)
	{
		std::cout << ", " << failed << " test" << (failed > 1 ? "s" : "") << " failed";
	}

	std::cout << std::endl;

	// Clean up memory
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		delete *it;
	}

	return 0;
}
