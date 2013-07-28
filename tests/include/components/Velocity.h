#ifndef COMENT_TESTS_VELOCITY_H
#define COMENT_TESTS_VELOCITY_H

namespace coment
{
        namespace tests
        {
		struct Velocity
			: public coment::Component
		{
			Velocity()
				: x(0), y(0)
			{

			}

			int x, y;
		};
	}
}

#endif /* COMENT_TESTS_VELOCITY_H */
