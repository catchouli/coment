#ifndef COMENT_BALLS_RADIUS_H
#define COMENT_BALLS_RADIUS_H

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			struct Radius
				: public coment::Component
			{
				Radius()
					: radius(0)
				{

				}

				Radius(float radius)
					: radius(radius)
				{

				}

				float radius;
			};
		}
	}
}

#endif /* COMENT_BALLS_RADIUS_H */
