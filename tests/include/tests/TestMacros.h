#ifndef COMENT_TESTS_TESTMACROS_H
#define COMENT_TESTS_TESTMACROS_H

#include <iostream>
#include <sstream>

#define success()		{ testsRun++; testsSucceeded++; std::cout << std::setw(0) << "Success" << std::endl; }
#define failure()		{ testsRun++; std::cout << std::setw(0) << "Failure" << std::endl; }

#define begintest(x)								\
{										\
	std::stringstream ss;							\
	ss << x;								\
	std::cout << "  " << std::left << std::setw(70) << ss.str();		\
}

#define endtest(x)								\
{										\
	if (x)									\
		success()							\
	else									\
		failure()							\
}

#endif /* COMENT_TESTS_TESTMACROS_H */
