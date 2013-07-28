#ifndef COMENT_BALLS_POSITION_H
#define COMENT_BALLS_POSITION_H

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			struct Position
				: public coment::Component
			{
				Position()
					: x(0), y(0)
				{

				}

				Position(float x, float y)
					: x(x), y(y)
				{

				}

				float x, y;
			};
		}
	}
}

#endif /* COMENT_BALLS_POSITION_H */
