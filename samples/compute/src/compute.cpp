#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <ctime>

#include "util/FileIO.h"
#include "util/SDLInit.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
    std::cout << coment::readFile("test");

    bool running = true;

    // SDL stuff
    auto sdlState = coment::initSDL(WINDOW_WIDTH, WINDOW_HEIGHT, "Compute");

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

        // Test
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.8f);
        glVertex2f(0.8f, -0.8f);
        glVertex2f(-0.8f, -0.8f);
        glEnd();

        // Flip buffers
        SDL_GL_SwapWindow(sdlState->window);
    }

    return 0;
}