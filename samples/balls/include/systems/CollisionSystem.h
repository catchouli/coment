#ifndef COMENT_BALLS_COLLISIONSYSTEM_H
#define COMENT_BALLS_COLLISIONSYSTEM_H

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"

#define COMENT_ABS(x) (x >= 0 ? x : -x)

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class CollisionSystem
				: public coment::EntityProcessingSystem
			{
			public:
				CollisionSystem()
				{

				}

				void registerComponents()
				{
					// Register required components
					registerComponent<Position>();
					registerComponent<Velocity>();
					registerComponent<Radius>();
				}

				virtual void onBegin()
				{
					_width = _world->getValue<int>("window_width");
					_height = _world->getValue<int>("window_height");
				}

				virtual void process(const coment::Entity& e)
				{
					const float DAMPENING_VERTICAL = 0.95f;
					const float DAMPENING_HORIZONTAL = 0.95f;

					Position* position = _world->getComponent<Position>(e);
					Velocity* velocity = _world->getComponent<Velocity>(e);
					Radius* radius = _world->getComponent<Radius>(e);

					// If we hit a wall, bounce and apply a dampening coefficient
					if ((position->x - radius->radius < 0 && velocity->x < 0) || (position->x + radius->radius > _width && velocity->x > 0))
					{
						velocity->x = -velocity->x * DAMPENING_HORIZONTAL;
					}
					if ((position->y - radius->radius < 0 && velocity->y < 0) || (position->y + radius->radius > _height && velocity->y > 0))
					{
						velocity->y = -velocity->y * DAMPENING_VERTICAL;
					}
				}

			private:
				int _width, _height;
			};
		}
	}
}

#endif /* COMENT_BALLS_COLLISIONSYSTEM_H */
