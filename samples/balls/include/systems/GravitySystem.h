#ifndef __GRAVITYSYSTEM_H__
#define __GRAVITYSYSTEM_H__

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

#endif /* __GRAVITYSYSTEM_H__ */
