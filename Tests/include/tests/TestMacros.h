#ifndef __TESTMACROS_H__
#define __TESTMACROS_H__

#include <iostream>
#include <sstream>

#define success()		{ testsRun++; testsSucceeded++; std::cout << std::setw(0) << "Success" << std::endl; }
#define failure()		{ testsRun++; std::cout << std::setw(0) << "Failure" << std::endl; }

#define begintest(x)								\
{										\
	std::stringstream ss;							\
	ss << x;								\
	std::cout << " " << std::left << std::setw(70) << ss.str();		\
}

#define endtest(x)								\
{										\
	if (x)									\
		success()							\
	else									\
		failure()							\
}

#endif /* __TESTMACROS_H__ */
