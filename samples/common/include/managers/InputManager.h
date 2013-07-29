#ifndef COMENT_BALLS_INPUTMANAGER_H
#define COMENT_BALLS_INPUTMANAGER_H

#include <SDL2/SDL.h>

#include <coment/systems/EntitySystem.h>
#include <coment/managers/Manager.h>

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class RenderingSystem;
			class CollisionSystem;
			class MovementSystem;
			class GravitySystem;

			class InputManager
				: public coment::Manager
			{
			public:
				InputManager();

				void handleEvent(const SDL_Event& e);

				void registered();

			private:
				coment::EntitySystem* _renderingSystem;
				coment::EntitySystem* _collisionSystem;
				coment::EntitySystem* _movementSystem;
				coment::EntitySystem* _gravitySystem;
			};

			InputManager::InputManager()
			{

			}

			// Called when this manager is registered with the world
			void InputManager::registered()
			{
				_renderingSystem = (coment::EntitySystem*)_world->getSystem<RenderingSystem>();
				_collisionSystem = (coment::EntitySystem*)_world->getSystem<CollisionSystem>();
				_movementSystem = (coment::EntitySystem*)_world->getSystem<MovementSystem>();
				_gravitySystem = (coment::EntitySystem*)_world->getSystem<GravitySystem>();
			}

			void InputManager::handleEvent(const SDL_Event& event)
			{
				// End when the user closes the window or presses esc
				if (event.type == SDL_QUIT ||
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				{
					_world->setValue<bool>("running", false);
				}

				// Handle keyboard input
				if (event.type == SDL_KEYDOWN)
				{
					// Toggle rendering when player presses R
					if (event.key.keysym.sym == SDLK_r)
					{
						_renderingSystem->setEnabled(!_renderingSystem->getEnabled());
						_world->setValue("rendering_enabled", _renderingSystem->getEnabled());
					}
					// Toggle movement when player presses M
					else if (event.key.keysym.sym == SDLK_m)
					{
						_collisionSystem->setEnabled(!_collisionSystem->getEnabled());
						_movementSystem->setEnabled(!_movementSystem->getEnabled());
						_gravitySystem->setEnabled(!_gravitySystem->getEnabled());
					}
					// Add 10 balls when user presses right arrow
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						_world->getManager<BallManager>()->createBalls(10);
					}
					// Remove 10 balls when user presses left arrow
					else if (event.key.keysym.sym == SDLK_LEFT)
					{
						_world->getManager<BallManager>()->destroyBalls(10);
					}
				}
			}
		}
	}
}

#endif /* COMENT_BALLS_INPUTMANAGER_H */
