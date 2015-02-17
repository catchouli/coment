#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace coment
{
    struct SDL_State final
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GLContext context;
    };

    void sdlStateDeleter(SDL_State* ptr);

    std::shared_ptr<SDL_State> initSDL(int width, int height, const char* title);
}