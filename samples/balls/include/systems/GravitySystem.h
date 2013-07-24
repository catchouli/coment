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

				void process(coment::Entity e)
				{
					Velocity* velocity = _world->getComponent<Velocity>(e);

					velocity->y += _world->getDelta() * GRAVITY_ACCELERATION;
				}

			private:
				static const int GRAVITY_ACCELERATION = 50;
			};
		}
	}
}

#endif /* __GRAVITYSYSTEM_H__ */
