#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <sdl_ttf.h> // <-- Para Fuentes de letra	BUSCAR FUENTE CON NUMEROS PARA IMPRIMIR LA SCORE!!

/*

	Para crear fuentes:
		Solo se cargan una vez.
		Necesitamos crear una "SURFACE" para meter las texturas (Solo necesitamos crear una sola SURFACE)
		Crear textura -> Crear rectangulo
		Le ponemos el texto encima

		INIT:
		if(!TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

		QUIT:
		TTF_Quit();

		TEXT:
		TTF_Font *font MIRALO EN EL MOVIL ANDA

		LINEAS INACABADAS
		...... "My first SDL game", SDL_Color{ 255, 150, 0, 255}) };

		...... (m_renderer. tmpSurf) };

		LINEA QUE NO SE VE EN LA FOTO
		SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect));

*/

#include <sdl_mixer.h> // <-- Para sonido

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 1600//800
#define SCREEN_HEIGHT 900//600

int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// FUENTES

	if (!TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer /*=*/ { SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//-->Animated Sprite ---

	// --- TEXT ---

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE/*ESCAPE*/) isRunning = false;
				break;
			default:;
			}
		}

		// UPDATE

			// Cambiar objetos de lugar, eliminar objetos...

		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();

	return 0;
}