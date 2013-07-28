#ifndef COMENT_TESTS_POSITION_H
#define COMENT_TESTS_POSITION_H

namespace coment
{
        namespace tests
        {
		struct Position
			: public coment::Component
		{
			Position()
				: x(0), y(0)
			{

			}

			int x, y;
		};
	}
}

#endif /* COMENT_TESTS_POSITION_H */
