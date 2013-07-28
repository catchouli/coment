#ifndef COMENT_BALLS_VELOCITY_H
#define COMENT_BALLS_VELOCITY_H

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			struct Velocity
				: public coment::Component
			{
				Velocity()
					: x(0), y(0)
				{

				}

				Velocity(float x, float y)
					: x(x), y(y)
				{

				}

				float x, y;
			};
		}
	}
}

#endif /* COMENT_BALLS_VELOCITY_H */
