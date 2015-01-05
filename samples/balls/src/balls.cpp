#include <iostream>
#include <SDL2/SDL.h>

#include <coment/World.h>

void initSDL(SDL_Window** window, SDL_Renderer** renderer);
void deinitSDL(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char** argv)
{
    bool running = true;

    // SDL stuff
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Initialise SDL
    initSDL(&window, &renderer);

    // Entity system
    coment::World world;

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

    }

    // Clean up
    deinitSDL(window, renderer);

    return 0;
}

void initSDL(SDL_Window** window, SDL_Renderer** renderer)
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
        800, 600, SDL_WINDOW_SHOWN);

    // Create a renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void deinitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}