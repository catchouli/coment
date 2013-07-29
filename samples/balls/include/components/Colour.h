#ifndef COMENT_BALLS_COLOUR_H
#define COMENT_BALLS_COLOUR_H

namespace coment
{
	namespace samples
	{
		namespace balls
		{
			class Colour
				: public coment::Component
			{
			public:
				Colour()
					: colour(0)
				{

				}

				Colour(int r, int g, int b, int a = 0)
					: colour(Colour::createFromRGBA(r, g, b, a).colour)
				{

				}

				static Colour createFromRGBA(int r, int g, int b, int a)
				{
					Colour c;
					c.colour = a + (b << 8) + (g << 16) + (r << 24);
					return c;
				}

				unsigned int colour;
			};
		}
	}
}

#endif /* COMENT_BALLS_COLOUR_H */
