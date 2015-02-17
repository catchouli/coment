#include <SDL2/SDL.h>
#include <stdexcept>
#include <GL/glew.h>
#include "util/SDLInit.h"

namespace coment
{
    void sdlStateDeleter(SDL_State* ptr)
    {
        SDL_GL_DeleteContext(ptr->context);
        SDL_DestroyRenderer(ptr->renderer);
        SDL_DestroyWindow(ptr->window);
        delete ptr;
    }

    std::shared_ptr<SDL_State> initSDL(int width, int height, const char* title)
    {
        std::shared_ptr<SDL_State> state = std::shared_ptr<SDL_State>(new SDL_State, sdlStateDeleter);

        // Initialise SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // Create a window
        state->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        // Create a renderer
        state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
        if (state->renderer == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // Create an opengl context
        state->context = SDL_GL_CreateContext(state->window);

        // Initialise GLEW
        glewInit();

        return state;
    }
}