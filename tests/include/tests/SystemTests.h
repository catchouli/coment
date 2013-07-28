#ifndef COMENT_TESTS_SYSTEMTESTS_H
#define COMENT_TESTS_SYSTEMTESTS_H

#include "Test.h"

namespace coment
{
	namespace tests
	{
		class SystemTests
			: public Test
		{
		public:
			SystemTests();

			void run();
		};
	}
}

#endif /* COMENT_TESTS_SYSTEMTESTS_H */
