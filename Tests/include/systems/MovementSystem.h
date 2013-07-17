#ifndef __MOVEMENTSYSTEM_H__
#define __MOVEMENTSYSTEM_H__

#include "components/Position.h"
#include "components/Velocity.h"

namespace coment
{
        namespace tests
        {
		class MovementSystem : public coment::EntityProcessingSystem
		{
		public:
			MovementSystem()
				: _registered(false)
			{

			}

			void registerComponents()
			{
				// Register required components
				registerComponent<Position>();
				registerComponent<Velocity>();
			}

			void onRegistered()
			{
				_registered = true;
			}

			virtual void process(coment::Entity e)
			{
				Position* position = _world->getComponent<Position>(e);
				Velocity* velocity = _world->getComponent<Velocity>(e);

				// Update position
				position->x += velocity->x * (int)_world->getDelta();
				position->y += velocity->y * (int)_world->getDelta();
			}

			bool isRegistered()
			{
				return _registered;
			}

		private:
			bool _registered;
		};
	}
}

#endif /* __MOVEMENTSYSTEM_H__ */
