#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#define SFML_STATIC

// Coment includes
#include <World.h>
#include <systems/EntityProcessingSystem.h>

// Custom managers
#include "managers/BallManager.h"
#include "managers/InputManager.h"

// Custom systems
#include "systems/RenderingSystem.h"
#include "systems/MovementSystem.h"

// Custom components
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

// Other includes
#include <SFML/Graphics.hpp>

#include <random>

const int WIDTH = 800;
const int HEIGHT = 600;
const int INITIAL_BALLS = 10;

int main(int argc, char** argv) 
{
	srand((unsigned int)time(0));

	// Create window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Coment SFML Test");
	window.setVisible(true);

	for (int i = 0; i < 1; ++i)
	{
		// Create entity world
		coment::World world;

		// Add systems to the world
		RenderingSystem* renderingSystem = world.addSystem(new RenderingSystem(&window));
		MovementSystem* movementSystem = world.addSystem(new MovementSystem(WIDTH, HEIGHT));
	
		// Add managers to world
		BallManager* ballManager = world.addManager<BallManager>();
		InputManager* inputManager = world.addManager<InputManager>();

		// Initialise managers
		ballManager->setDimensions(WIDTH, HEIGHT);
		inputManager->initialise(&window, renderingSystem, movementSystem);

		// Create some balls
		ballManager->createBalls(INITIAL_BALLS);
	}

	_CrtDumpMemoryLeaks();

	// Create entity world
	coment::World world;

	// Add systems to the world
	RenderingSystem* renderingSystem = world.addSystem(new RenderingSystem(&window));
	MovementSystem* movementSystem = world.addSystem(new MovementSystem(WIDTH, HEIGHT));
	
	// Add managers to world
	BallManager* ballManager = world.addManager<BallManager>();
	InputManager* inputManager = world.addManager<InputManager>();

	// Initialise managers
	ballManager->setDimensions(WIDTH, HEIGHT);
	inputManager->initialise(&window, renderingSystem, movementSystem);

	// Create some balls
	ballManager->createBalls(INITIAL_BALLS);

	// Create a clock to manage time
	sf::Clock clock;

	// Update the window
	while (window.isOpen()) 
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			inputManager->handleEvent(event);
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
		char buf[1024];
		sprintf_s(buf, "%i Balls, %.0f FPS, Rendering %s (Press R), Movement %s (Press M), right/left arrow keys to add/remove balls", world.getManager<BallManager>()->getBallCount(), 1.0f / world.getDelta(), (renderingSystem->getEnabled() ? "Enabled" : "Disabled"), (movementSystem->getEnabled() ? "Enabled" : "Disabled"));
		window.setTitle(buf);
	}

	return 0;
}