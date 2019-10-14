#include <SDL.h>
#include <exception>
#include <iostream>
#include <string>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void Init(SDL_Window* &m_window, SDL_Renderer* &m_renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	m_window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Close(SDL_Window* &m_window, SDL_Renderer* &m_renderer) {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	try {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		Init(window, renderer);
		SDL_Event e;
		bool quit = false;
		SDL_Color newColor{ 0,0,0 }, prevColor{ 0,0,0 };
		float percent = 0.0f;
		auto lerp = [](float v0, float v1, float t) { return (1 - t)*v0 + t * v1; };
		while (!quit) {
			if (!SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
			}
			SDL_RenderClear(renderer);
			(percent > 1.0f) ? (prevColor = newColor, newColor = { Uint8(rand() % 0xFF), Uint8(rand() % 0xFF), Uint8(rand() % 0xFF) }, percent = 0.0f)
				: percent += .0002f;
			SDL_SetRenderDrawColor(renderer, lerp(prevColor.r, newColor.r, percent), lerp(prevColor.g, newColor.g, percent), lerp(prevColor.b, newColor.b, percent), 0xFF);
			SDL_RenderPresent(renderer);
		}
		Close(window, renderer);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		auto sdlError = SDL_GetError();
		if (strlen(sdlError)) std::cout << "SDL Error: " << sdlError << std::endl;
		std::cin.get();
	}
	return 0;
}