#ifndef COMENT_COMMON_INITIALISATION
#define COMENT_COMMON_INITIALISATION

namespace coment
{
	namespace samples
	{
		SDL_Window* createWindow(const char* title, int width, int height);
		SDL_Renderer* createRenderer(SDL_Window* window);
		SDL_Texture* createTexture(SDL_Renderer* renderer, int width, int height);
	}
}

#endif /* COMENT_COMMON_INITIALISATION */

