#ifndef __VARIABLETESTS_H__
#define __VARIABLETESTS_H__

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

#endif /* __VARIABLETESTS_H__ */
