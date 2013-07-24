#ifndef __COLLISIONSYSTEM_H__
#define __COLLISIONSYSTEM_H__

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"

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
				CollisionSystem(float width, float height)
					: _width(width), _height(height)
				{

				}

				void registerComponents()
				{
					// Register required components
					registerComponent<Position>();
					registerComponent<Velocity>();
					registerComponent<Radius>();
				}

				virtual void process(coment::Entity e)
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
				float _width, _height;
			};
		}
	}
}

#endif /* __COLLISIONSYSTEM_H__ */
