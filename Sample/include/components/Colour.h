#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <SFML/Graphics.hpp>

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

#endif /* __COLOUR_H__ */
