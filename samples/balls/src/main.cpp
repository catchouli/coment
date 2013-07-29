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
#include "systems/CollisionSystem.h"
#include "systems/MovementSystem.h"
#include "systems/GravitySystem.h"

// Components
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

// Drawing
#include "graphics/PixelBuffer.h"

// SDL
#include <SDL2/SDL.h>

using namespace coment::samples::balls;

// Forward declarations
void drawCircle(unsigned int* buffer, int bufferWidth, int bufferHeight, int colour, int radius, int x, int y);
void draw4lines(unsigned int* buffer, int bufferWidth, int bufferHeight, int colour, int cx, int cy, int x, int y);
void draw2lines(unsigned int* buffer, int bufferWidth, int bufferHeight, int colour, int cx, int cy, int x, int y);
void drawhline(unsigned int* buffer, int bufferWidth, int bufferHeight, int colour, int x1, int x2, int y);

// Window size
int width = 800;
int height = 600;

// Constants
const int INITIAL_WIDTH = 800;
const int INITIAL_HEIGHT = 600;
const int DEPTH = 32;

const int CLEAR_COLOUR = 0xFFFFFFFF;

const int INITIAL_BALLS = 1000;
const float GAME_SPEED = 0.002f;

int main(int argc, char** argv)
{
	// Timing
	unsigned int lastUpdate;
	unsigned int thisUpdate;
	unsigned int dt = 0;

	// FPS
	int frames = 0;
	int fps = 0;
	int lastFPSUpdate;

	// Pixel buffer
	PixelBuffer pixelBuffer(width, height);

	// SDL structures
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* renderTexture;

	// Seed random number generator
	srand((unsigned int)time(0));

	// Initialise SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Initilialise timing
	lastUpdate = thisUpdate = SDL_GetTicks();
	lastFPSUpdate = lastUpdate;

	// Create window
	window = SDL_CreateWindow("Balls", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	if (window == NULL)
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return -1;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
		return -1;
	}

	// Create render texture
	renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	if (renderTexture == NULL)
	{
		fprintf(stderr, "Failed to create render texture: %s\n", SDL_GetError());
		return -1;
	}

	// Create entity world
	coment::World world;

	// Set window values
	world.setValue<int>("window_width", INITIAL_WIDTH);
	world.setValue<int>("window_height", INITIAL_HEIGHT);

	// Create and initialise systems
	RenderingSystem renderingSystem(&pixelBuffer);
	CollisionSystem collisionSystem;
	MovementSystem movementSystem;
	GravitySystem gravitySystem;

	// Add systems to world
	world.registerSystem(renderingSystem);
	world.registerSystem(collisionSystem);
	world.registerSystem(movementSystem);
	world.registerSystem(gravitySystem);

	// Create and initialise managers
	BallManager ballManager(width, height);
	InputManager inputManager;

	// Add managers to world
	world.registerManager(ballManager);
	world.registerManager(inputManager);

	// Create some balls
	ballManager.createBalls(INITIAL_BALLS);

	// Start main loop
	world.setValue<bool>("running", true);
	while (world.getValue<bool>("running"))
	{
		const SDL_Rect screenRect = {0, 0, width, height};

		// Update timer
		thisUpdate = SDL_GetTicks();
		dt = thisUpdate - lastUpdate;

		// Handle all events
		while (SDL_PollEvent(&event))
		{
			inputManager.handleEvent(event);
		}

		// Update game
		world.loopStart();
		world.setDelta(dt*GAME_SPEED);

		// Run update systems
		collisionSystem.update();
		movementSystem.update();
		gravitySystem.update();

		// Clear window
		SDL_RenderClear(renderer);

		// Clear buffer
		pixelBuffer.clear(CLEAR_COLOUR);

		// Run rendering system
		renderingSystem.update();

		// Blit buffer to screen renderer
		SDL_UpdateTexture(renderTexture, &screenRect, pixelBuffer.getBuffer(), world.getValue<int>("window_width") * 4);

		// Render texture to screen
		SDL_RenderCopy(renderer, renderTexture, &screenRect, &screenRect);

		// Flip screen buffer
		SDL_RenderPresent(renderer);

		// Update last time
		lastUpdate = thisUpdate;

		// Average FPS calculations
		frames++;
		if (thisUpdate - lastFPSUpdate >= 1000)
		{
			char titleBuffer[256];

			// Update FPS counters
			fps = frames;
			frames = 0;
			lastFPSUpdate = thisUpdate;

			// Output window title
			printf("FPS: %d\n", fps);
		}
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
