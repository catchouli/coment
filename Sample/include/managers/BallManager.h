#ifndef __BallManager_H__
#define __BallManager_H__

#include <string>
#include <map>
#include <random>

#include <managers/Manager.h>

#include <utils/Bag.h>

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

#include <SFML/Graphics.hpp>

class BallManager
	: public coment::Manager<BallManager>
{
public:
	BallManager(int width, int height);
	
	void createBalls(int number);
	void destroyBalls(int number);

	int getBallCount();

private:
	int _windowWidth;
	int _windowHeight;

	coment::Bag<coment::Entity> _balls;
};

BallManager::BallManager(int width, int height)
	: _windowWidth(width), _windowHeight(height)
{

}

void BallManager::createBalls(int number)
{
	for (int i = 0; i < number; ++i)
	{
		// Create a ball
		coment::Entity e = _world->createEntity();

		// At a random position on the screen
		_world->addComponent(e, Position(rand() % _windowWidth, rand() % _windowHeight));

		// With a random velocity between (10, 10) and (100, 100)
		_world->addComponent(e, Velocity(rand() % 90 + 10, rand() % 90 + 10));

		// A random radius between 10 and 50
		_world->addComponent(e, Radius(rand() % 40 + 10));

		// And a random colour
		_world->addComponent(e, Colour(rand() % 255, rand() % 255, rand() % 255));

		// Refresh systems with entity
		_world->refresh(e);

		// Add entity to bag
		_balls.add(e);
	}
}

void BallManager::destroyBalls(int number)
{
	for (int i = 0; i < number; ++i)
	{
		_world->remove(_balls.getLast());
	}
}

int BallManager::getBallCount()
{
	return _balls.getSize();
}

#endif /* __BallManager_H__ */
