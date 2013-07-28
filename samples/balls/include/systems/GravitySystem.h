#ifndef COMENT_BALLS_GRAVITYSYSTEM_H
#define COMENT_BALLS_GRAVITYSYSTEM_H

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class GravitySystem
				: public coment::EntityProcessingSystem
			{
			public:
				void registerComponents()
				{
					// Register required components
					registerComponent<Velocity>();
				}

				void process(const coment::Entity& e)
				{
					const float GRAVITY_ACCELERATION = 250;

					Velocity* velocity = _world->getComponent<Velocity>(e);

					velocity->y += _world->getDelta() * GRAVITY_ACCELERATION;
				}
			};
		}
	}
}

#endif /* COMENT_BALLS_GRAVITYSYSTEM_H */
