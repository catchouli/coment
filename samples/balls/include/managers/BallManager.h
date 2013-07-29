#ifndef COMENT_BALLS_BALLMANAGER_H
#define COMENT_BALLS_BALLMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

#include <coment/managers/Manager.h>

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

#include <SFML/Graphics.hpp>

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class BallManager
				: public coment::Manager
			{
			public:
				BallManager(int width, int height);

				void setDimensions(int width, int height);

				void createBalls(int number);
				void destroyBalls(int number);

				int getBallCount() const;

			private:
				int _windowWidth;
				int _windowHeight;

				static const int MIN_RADIUS = 10;
				static const int MAX_RADIUS = 50;

				static const int MIN_INITIAL_VELOCITY_X = 50;
				static const int MAX_INITIAL_VELOCITY_X = 150;
				static const int MIN_INITIAL_VELOCITY_Y = 50;
				static const int MAX_INITIAL_VELOCITY_Y = 150;

				std::vector<coment::Entity> _balls;
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
					Position* pos = _world->addComponent<Position>(e);
					pos->x = (float)(rand() % _windowWidth);
					pos->y = (float)(rand() % _windowHeight);

					// With a random velocity between (10, 10) and (100, 100)
					Velocity* vel = _world->addComponent<Velocity>(e);
					vel->x = (float)(rand() % (MAX_INITIAL_VELOCITY_X - MIN_INITIAL_VELOCITY_X) + MIN_INITIAL_VELOCITY_X);
					vel->y = (float)(rand() % (MAX_INITIAL_VELOCITY_Y - MIN_INITIAL_VELOCITY_Y) + MIN_INITIAL_VELOCITY_Y);

					// A random radius between 10 and 50
					Radius* radius = _world->addComponent<Radius>(e);
					radius->radius = (float)(rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS);

					// And a random colour
					Colour* colour = _world->addComponent<Colour>(e);
					*colour = Colour::createFromRGBA(rand() % 255, rand() % 255, rand() % 255, 255);

					// Add entity to bag
					_balls.push_back(e);
				}
			}

			void BallManager::destroyBalls(int number)
			{
				for (int i = 0; i < number; ++i)
				{
					if (_balls.size() > 0)
					{
						_world->remove(_balls.back());
						_balls.pop_back();
					}
				}
			}

			int BallManager::getBallCount() const
			{
				return _balls.size();
			}
		}
	}
}

#endif /* COMENT_BALLS_BALLMANAGER_H */
