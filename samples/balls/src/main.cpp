#define SFML_STATIC

#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// Coment includes
#include <coment/World.h>

// Managers
#include "managers/BallManager.h"
#include "managers/InputManager.h"

// Systems
#include "systems/RenderingSystem.h"
#include "systems/MovementSystem.h"
#include "systems/GravitySystem.h"

// Components
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

// Other includes
#include <SFML/Graphics.hpp>

using namespace coment::samples::balls;

const int WIDTH = 800;
const int HEIGHT = 600;
const int INITIAL_BALLS = 10;

int main(int argc, char** argv)
{
	srand((unsigned int)time(0));

	// Create window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Coment SFML Test");
	window.setVisible(true);

	// Create entity world
	coment::World world;

	// Create and initialise systems
	RenderingSystem renderingSystem(&window);
	GravitySystem gravitySystem;
	MovementSystem movementSystem((float)WIDTH, (float)HEIGHT);

	// Add systems to world
	world.registerSystem(renderingSystem);
	world.registerSystem(gravitySystem);
	world.registerSystem(movementSystem);

	// Create and initialise managers
	BallManager ballManager(WIDTH, HEIGHT);
	InputManager inputManager(&window);

	// Add managers to world
	world.registerManager(ballManager);
	world.registerManager(inputManager);

	// Create some balls
	ballManager.createBalls(INITIAL_BALLS);

	// Create a clock to manage time
	sf::Clock clock;

	// Update the window
	while (window.isOpen())
	{
		std::stringstream ss;

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			inputManager.handleEvent(event);
		}

		// Clear the window
		window.clear(sf::Color(255, 255, 255, 255));

		// Begin loop
		world.loopStart();
		world.setDelta(clock.restart().asSeconds());

		// Process systems
		world.update();

		// Render window
		window.display();

		// Update title
		ss << world.getManager<BallManager>()->getBallCount() << " Balls, ";
		ss << 1.0f / world.getDelta() << " FPS, ";
		ss << "Rendering " << (renderingSystem.getEnabled() ? "Enabled" : "Disabled") << " (Press R), ";
		ss << "Movement " << (movementSystem.getEnabled() ? "Enabled" : "Disabled") << " (Press M), ";
		ss << "right/left arrow keys to add/remove balls";

		window.setTitle(ss.str().c_str());
	}

	return 0;
}
