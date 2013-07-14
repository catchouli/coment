#ifndef __VELOCITY_H__
#define __VELOCITY_H__

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

#endif /* __VELOCITY_H__ */
