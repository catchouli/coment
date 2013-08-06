#include "graphics/PixelBuffer.h"
#include <stdio.h>
#include <SDL2/SDL.h>
namespace coment
{
	namespace samples
	{
		SDL_Window* createWindow(const char* title, int width, int height)
		{
			SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

			if (window == NULL)
			{
				fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
				exit(-1);
			}

			return window;
		}

		SDL_Renderer* createRenderer(SDL_Window* window)
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == NULL)
			{
				fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
				exit(-1);
			}

			return renderer;
		}

		SDL_Texture* createTexture(SDL_Renderer* renderer, int width, int height)
		{
			SDL_Texture* renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

			if (renderTexture == NULL)
			{
				fprintf(stderr, "Failed to create render texture: %s\n", SDL_GetError());
				exit(-1);
			}

			return renderTexture;
		}
	}
}
