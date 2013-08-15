#ifndef COMENT_TESTS_MOVEMENTSYSTEM_H
#define COMENT_TESTS_MOVEMENTSYSTEM_H

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
				: _onRegisteredCalled(false), _onFirstUpdateCalled(false),
				  _onBeginCalled(false), _onEndCalled(false),
				  _onAddedCalled(false), _onRemovedCalled(false)
			{

			}

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
				position->x += velocity->x * (int)_world->getDelta();
				position->y += velocity->y * (int)_world->getDelta();
			}

			void onRegistered()
			{
				_onRegisteredCalled = true;
			}

			void onFirstUpdate()
			{
				_onFirstUpdateCalled = true;
			}

			void onBegin()
			{
				_onBeginCalled = true;
			}

			void onEnd()
			{
				_onEndCalled = true;
			}

			void onAdded(const Entity& e)
			{
				_onAddedCalled = true;
			}

			void onRemoved(const Entity& e)
			{
				_onRemovedCalled = true;
			}

			bool onRegisteredCalled()
			{
				return _onRegisteredCalled;
			}

			bool onFirstUpdateCalled()
			{
				return _onFirstUpdateCalled;
			}

			bool onBeginCalled()
			{
				return _onBeginCalled;
			}

			bool onEndCalled()
			{
				return _onEndCalled;
			}

			bool onAddedCalled()
			{
				return _onAddedCalled;
			}

			bool onRemovedCalled()
			{
				return _onRemovedCalled;
			}

			bool noEventsCalled()
			{
				return  !_onRegisteredCalled &&
					!_onFirstUpdateCalled &&
					!_onBeginCalled &&
					!_onEndCalled &&
					!_onAddedCalled &&
					!_onRemovedCalled;
			}

		private:
			bool _onRegisteredCalled;
			bool _onFirstUpdateCalled;
			bool _onBeginCalled;
			bool _onEndCalled;
			bool _onAddedCalled;
			bool _onRemovedCalled;
		};
	}
}

#endif /* COMENT_TESTS_MOVEMENTSYSTEM_H */
