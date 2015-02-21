#include <SDL2/SDL.h>
#include <stdexcept>
#include <GL/glew.h>

#include "util/SDLWindow.h"

namespace coment
{
    SDLWindow::SDLWindow(int width, int height, const char* title)
    {
        createWindow(width, height, title);
    }

    SDLWindow::~SDLWindow()
    {
        SDL_GL_DeleteContext(mContext);
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
    }

    void SDLWindow::createWindow(int width, int height, const char* title)
    {
        // Initialise SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // Create a window
        mWindow = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MOUSE_FOCUS);

        // Create a renderer
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        if (mRenderer == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // Create an opengl context
        mContext = SDL_GL_CreateContext(mWindow);

        // Initialise GLEW
        glewInit();
    }
}