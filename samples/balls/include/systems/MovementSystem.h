#ifndef COMENT_BALLS_MOVEMENTSYSTEM_H
#define COMENT_BALLS_MOVEMENTSYSTEM_H

#include "components/Position.h"
#include "components/Velocity.h"

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class MovementSystem
				: public coment::EntityProcessingSystem
			{
			public:
				void registerComponents()
				{
					// Register required components
					registerComponent<Position>();
					registerComponent<Velocity>();
				}

				virtual void process(const coment::Entity& e)
				{
					Position* position = _world->getComponent<Position>(e);
					Velocity* velocity = _world->getComponent<Velocity>(e);

					// Update position
					position->x += velocity->x * _world->getDelta();
					position->y += velocity->y * _world->getDelta();
				}
			};
		}
	}
}

#endif /* COMENT_BALLS_MOVEMENTSYSTEM_H */
