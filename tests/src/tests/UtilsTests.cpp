#include "tests/UtilsTests.h"

#include <coment/utils/BitMask.h>

namespace coment
{
	namespace tests
	{
		UtilsTests::UtilsTests()
			: Test("Utils")
		{

		}

		void UtilsTests::run()
		{
			BitMask bitMask;

			begintest("Bitmask [] operator works");
				bitMask.setBit(11);
			endtest(bitMask[11]);

			return;
		}
	}
}

