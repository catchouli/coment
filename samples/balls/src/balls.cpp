#include <iostream>
#include <set>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <coment/World.h>

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Color.h"

#include "systems/MovementSystem.h"
#include "systems/CircleCollisionSystem.h"
#include "systems/RenderingSystem.h"

void initSDL(SDL_Window** window, SDL_Renderer** renderer, SDL_GLContext* context);
void deinitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct system_t
{
    system_t(int priority = 0) : priority(priority) {}

    int priority;
};

struct SystemPtrComparator
{
    bool operator()(const system_t* lhs, const system_t* rhs)
    {
        return lhs->priority > rhs->priority;
    }
};

int main(int argc, char** argv)
{
    bool running = true;

    // SDL stuff
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext context;

    // Initialise SDL
    initSDL(&window, &renderer, &context);

    // Entity world
    coment::World world;

    // Add systems
    world.addSystem<MovementSystem>();
    world.addSystem<CircleCollisionSystem>(WINDOW_WIDTH, WINDOW_HEIGHT);
    world.addSystem<RenderingSystem>(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create circles with random positions, velocities, colours and radiuses
    srand(time(0));
    for (int i = 0; i < 10; ++i)
    {
        auto randf = []() { return rand() / (float)RAND_MAX; };
        auto randfr = [&randf](float min, float max) { return randf() * (max - min) + min; };

        coment::Entity e = world.createEntity();
        e.addComponent<Position>(randf() * WINDOW_WIDTH, randf() * WINDOW_HEIGHT);
        e.addComponent<Radius>(randfr(0.0f, 80.0f));
        e.addComponent<Velocity>(randfr(-350.0f, 350.0f), randfr(-350.0f, 350.0f));
        e.addComponent<Color>(randf(), randf(), randf());
    }

    // Main loop
    while (running)
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle window closure
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                // Let the program exit after this iteration ends
                running = false;
            }
        }

        // Process entities
        world.update();

        // Flip buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    deinitSDL(window, renderer, context);

    return 0;
}

void initSDL(SDL_Window** window, SDL_Renderer** renderer, SDL_GLContext* context)
{
    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a window
    *window = SDL_CreateWindow(
        "Balls!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Create a renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create an opengl context
    *context = SDL_GL_CreateContext(*window);
}

void deinitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context)
{
    // Clean up
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}