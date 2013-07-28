#ifndef COMENT_TESTS_VARIABLETESTS_H
#define COMENT_TESTS_VARIABLETESTS_H

#include "Test.h"

namespace coment
{
	namespace tests
	{
		class VariableTests
			: public Test
		{
		public:
			VariableTests();

			void run();
		};

		struct VariableTestStruct
		{
			VariableTestStruct() : value(45000) {}
			VariableTestStruct(int val) : value(val) {}

			int value;
		};
	}
}

#endif /* COMENT_TESTS_VARIABLETESTS_H */
