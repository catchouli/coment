#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace coment
{
    class SDLWindow final
    {
    public:

        SDLWindow(int width, int height, const char* title);

        ~SDLWindow();

        SDL_Window* getSDLWindow() const;
        SDL_Renderer* getSDLRenderer() const;
        SDL_GLContext getGLContext() const;

    private:

        void createWindow(int width, int height, const char* title);

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        SDL_GLContext mContext;

    };

    inline SDL_Window* SDLWindow::getSDLWindow() const
    {
        return mWindow;
    }

    inline SDL_Renderer* SDLWindow::getSDLRenderer() const
    {
        return mRenderer;
    }

    inline SDL_GLContext SDLWindow::getGLContext() const
    {
        return mContext;
    }
}