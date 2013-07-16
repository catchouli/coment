#ifndef __GRAVITYSYSTEM_H__
#define __GRAVITYSYSTEM_H__

#include <coment/utils/Bag.h>

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

					velocity->y += GRAVITY_ACCELERATION * _world->getDelta();
				}

			private:
				static const float GRAVITY_ACCELERATION = 50.0f;
			};
		}
	}
}

#endif /* __GRAVITYSYSTEM_H__ */
