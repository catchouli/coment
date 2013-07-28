#ifndef COMENT_BALLS_COLOUR_H
#define COMENT_BALLS_COLOUR_H

#include <SFML/Graphics.hpp>

namespace coment
{
	namespace samples
	{
		namespace balls
		{
			struct Colour : public coment::Component, sf::Color
			{
				Colour()
					: sf::Color(255, 255, 255, 255)
				{

				}

				Colour(int r, int g, int b)
					: sf::Color(r, g, b, 255)
				{

				}
			};
		}
	}
}

#endif /* COMENT_BALLS_COLOUR_H */
