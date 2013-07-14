#ifndef __MOVEMENTSYSTEM_H__
#define __MOVEMENTSYSTEM_H__

#include "components/Position.h"
#include "components/Velocity.h"

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class MovementSystem : public coment::EntityProcessingSystem
			{
			public:
				MovementSystem(float width, float height)
					: _width(width), _height(height)
				{

				}

				void registerComponents()
				{
					// Register required components
					registerComponent<Position>();
					registerComponent<Velocity>();
				}

				virtual void process(coment::Entity e)
				{
					Position* position = _world->getComponent<Position>(e);
					Velocity* velocity = _world->getComponent<Velocity>(e);
					Radius* radius = _world->getComponent<Radius>(e);

					// Update position
					position->x += velocity->x * _world->getDelta();
					position->y += velocity->y * _world->getDelta();

					// If we hit a wall, bounce
					if ((position->x - radius->radius < 0 && velocity->x < 0) || (position->x + radius->radius > _width && velocity->x > 0)) 
						velocity->x = -velocity->x;
					if ((position->y - radius->radius < 0 && velocity->y < 0) || (position->y + radius->radius > _height && velocity->y > 0))
						velocity->y = -velocity->y;
				}

			private:
				float _width, _height;
			};
		}
	}
}

#endif /* __MOVEMENTSYSTEM_H__ */
