#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <string>
#include <map>

#include <managers/Manager.h>
#include <SFML/Graphics.hpp>

#include <systems/EntitySystem.h>

class InputManager
	: public coment::Manager<InputManager>
{
public:
	InputManager(sf::RenderWindow* window, coment::EntitySystem* renderSystem, coment::EntitySystem* movementSystem);

	void handleEvent(const sf::Event& e);

private:
	sf::RenderWindow* _window;
	coment::EntitySystem* _renderSystem;
	coment::EntitySystem* _movementSystem;
};

InputManager::InputManager(sf::RenderWindow* window, coment::EntitySystem* renderSystem, coment::EntitySystem* movementSystem)
	: _window(window), _renderSystem(renderSystem), _movementSystem(movementSystem)
{
	
}

void InputManager::handleEvent(const sf::Event& event)
{
	// End when the user closes the window or presses esc
	if (event.type == sf::Event::Closed ||
		(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		_window->close();
	}

	// Handle keyboard input
	if (event.type == sf::Event::KeyReleased)
	{
		// Disable rendering when player presses R
		if (event.key.code == sf::Keyboard::R)
		{
			_renderSystem->setEnabled(!_renderSystem->getEnabled());
		}
		// Disable movement when player presses M
		else if (event.key.code == sf::Keyboard::M)
		{
			_movementSystem->setEnabled(!_movementSystem->getEnabled());
		}
		// Add 100 balls when user presses right arrow
		else if (event.key.code == sf::Keyboard::Right)
		{
			_world->getManager<BallManager>().createBalls(100);
		}
		// Remove 100 balls when user presses left arrow
		else if (event.key.code == sf::Keyboard::Left)
		{
			//_world->getManager<BallManager>().destroyBalls(1);
		}
	}
}

#endif /* __INPUTMANAGER_H__ */
