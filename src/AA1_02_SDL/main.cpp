#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sdl_mixer.h> // <-- Para sonido

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CURSOR_WIDTH 60
#define CURSOR_HEIGHT 40

#define PLAYER_WIDTH 400
#define PLAYER_HEIGHT 75

int main(int, char*[])
{

	struct position {

		int x = 0;
		int y = 0;

	};

	position mouse;

	position player;
	player.x = (SCREEN_WIDTH / 2) - (PLAYER_WIDTH/2);
	player.y = (SCREEN_HEIGHT / 2) - (PLAYER_HEIGHT/2);
	
	
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF

	if (TTF_Init() == -1) throw "No es pot inicialitzar la llibreria TTF";

	TTF_Font *font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 100);
	if (font == nullptr) throw "No es pot obrir la font";

	//-->SDL_Mix

	const Uint8 mixFlags(MIX_INIT_MP3 | MIX_INIT_OGG);
	
	/// NO SE ABRE PORQUE EL MONITOR NO TIENE ALTAVOZ !!!
	/*if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {	// NO SE ABRE
		throw "No es pot inicialitzar SDL_mixer audio systems";
	}

	Mix_Music *SoundTrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!SoundTrack) throw "No es pot carregar el Mix_Music SoundTrack";

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(SoundTrack, -1);*/
	

	// --- BUTTONS ---

	SDL_Color basic{ 255,255,255, 255 };

	std::string playText = "PLAY";
	std::string musicText = "MUSIC";
	std::string exitText = "EXIT";

	SDL_Color playColor{ 255, 0, 0 , 255 }, playColor2{ 0,255, 0, 255 }; // ROJO Y VERDE
	SDL_Color musicColor{ 255, 255, 0 , 255 };
	SDL_Color exitColor{ 0, 0, 255 , 255 };

	SDL_Color playColor1 = playColor; // PARA COLOR ORIGINAL
	SDL_Color musicColor1 = musicColor;
	SDL_Color exitColor1 = exitColor;

	SDL_Color playColorH1{ 150, 0, 0 , 255 }, playColorH2{ 0,150,0,255 };
	SDL_Color musicColorH{ 150, 150, 0, 255 };
	SDL_Color exitColorH{ 0, 0, 150, 255 };

	SDL_Surface *playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColor);  // RESUELTO No se puede crear porque la fuente es nullptr
	SDL_Surface *musicSurface = TTF_RenderText_Blended(font, musicText.c_str(), musicColor);
	SDL_Surface *exitSurface = TTF_RenderText_Blended(font, exitText.c_str(), exitColor);

	SDL_Rect playButton{ SCREEN_WIDTH / 3/*0*/, SCREEN_HEIGHT / 5/*0*/, 100, 40 };
	SDL_Rect musicButton{ SCREEN_WIDTH / 2/*SCREEN_WIDTH-100*/, SCREEN_HEIGHT / 5/*SCREEN_HEIGHT-40*/, 100, 40};
	SDL_Rect exitButton{ SCREEN_WIDTH - (SCREEN_WIDTH / 3)/*0*/, SCREEN_HEIGHT / 5/*SCREEN_HEIGHT-40*/, 100, 40};

	SDL_Texture *playTexture = SDL_CreateTextureFromSurface(m_renderer, playSurface);	// NORMAL TEXTURE
	SDL_Texture *musicTexture = SDL_CreateTextureFromSurface(m_renderer, musicSurface);
	SDL_Texture *exitTexture = SDL_CreateTextureFromSurface(m_renderer, exitSurface);


	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//mouse.x = event.motion.x;
	//mouse.y = event.motion.y;

		//Cursor
	SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") }; //kintoun.png
	if (cursorTexture == nullptr) throw "Error: cursorTexture init";
	SDL_Rect cursorRect{/*Coordenadas X e Y del ratón*/ mouse.x, mouse.y, CURSOR_WIDTH, CURSOR_HEIGHT };

	//-->Animated Sprite ---

	SDL_Texture* playerTexture { IMG_LoadTexture(m_renderer, "../../res/img/sp01.png") };
	SDL_Rect spriteRect{ player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect playerRect{ spriteRect.x, spriteRect.y, PLAYER_WIDTH/6, PLAYER_HEIGHT };

	// --- TEXT ---

	// --- AUDIO ---


	// --- GAME LOOP ---

	SDL_Event event;
	bool isRunning = true;
	bool click = false;
	bool music = true;

	bool play = false;
	bool playH = false;

	bool colorChanged = false;

	/*mouse.x = event.motion.x;
	mouse.y = event.motion.y;*/

	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:

				/*mouse.x = event.motion.x;
				mouse.y = event.motion.y;*/

				cursorRect.x = event.motion.x - CURSOR_WIDTH / 2; //mouse.x;
				cursorRect.y = event.motion.y - CURSOR_HEIGHT / 2; //mouse.y;

				// Para que no se salga de los bordes	// pues no hace falta parece
				//if (cursorRect.x > SCREEN_WIDTH) cursorRect.x = 0; /*SCREEN_WIDTH - (CURSOR_WIDTH / 2);*/
				//if (cursorRect.y > SCREEN_HEIGHT) cursorRect.y = 0; /*SCREEN_HEIGHT - (CURSOR_HEIGHT / 2);*/

				break;

			case SDL_MOUSEBUTTONDOWN:

				/*if (!click) { click = true; }
				else { click = false; }*/

				click = true;

			break;

			case SDL_MOUSEBUTTONUP:

			//click = false;

			break;

			default: break;
			}
		}

		// UPDATE	// NO SE CREAN TEXTURAS NI OSTIES, TODO SE CREA ANTES DEL GAMELOOP

		//SDL_

		// if mouse está dentro de un botón ---> MIRAR EN QUÉ BOTÓN ESTÁ Y PONERLO EN HOVER

		// if click en EXIT --> isRunning = false;

		// if click en PLAY --> cambiar su color

		// if click en MUSIC --> MUSIC a -1 (se apaga la música)


		 // CLICK

		if (click && event.motion.x > playButton.x && event.motion.x < (playButton.x + playButton.w) && event.motion.y > playButton.y && event.motion.y < (playButton.y + playButton.h)) {

			if (play) { play = false; }
			else if (!play) { play = true; }

			//if (!colorChanged) {/*PONER COLOR 2*/ ; colorChanged = true; } // SE HACE ABAJO
			//else			     {/*PONER COLOR 1*/ ; colorChanged = false; }

		} else if (click && event.motion.x > musicButton.x && event.motion.x < (musicButton.x + musicButton.w) && event.motion.y > musicButton.y && event.motion.y < (musicButton.y + musicButton.h)) {

			if (music) { music = false; }
			else { music = true; }

		} else if (click && event.motion.x > exitButton.x && event.motion.x < (exitButton.x + exitButton.w) && event.motion.y > exitButton.y && event.motion.y < (exitButton.y + exitButton.h)) {
			isRunning = false;
		}



		if (music) {/*Mix_PlayMusic(SoundTrack, -1);*/ /*APAGAR MUSICA*/ }
		else if (!music) {/*Mix_PlayMusic(SoundTrack, 1);*/ /*ENCENDER MUSICA*/ }

		

		// HOVER

		if (event.motion.x > playButton.x && event.motion.x < (playButton.x + playButton.w) && event.motion.y > playButton.y && event.motion.y < (playButton.y + playButton.h)) {
			/*COLOR HOVER*/
			/*if (play) {																	// ESTO YA SE HACE ABAJO
				playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColorH2);
			}
			else { playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColorH1); }*/
			playH = true;
		}
		else {/*COLOR NORMAL*/
			playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColor1); playH = false;

		}

		if (event.motion.x > musicButton.x && event.motion.x < (musicButton.x + musicButton.w) && event.motion.y > musicButton.y && event.motion.y < (musicButton.y + musicButton.h)) {
			/*COLOR HOVER*/
			musicSurface = TTF_RenderText_Blended(font, musicText.c_str(), musicColorH);
		}
		else {/*COLOR NORMAL*/
			musicSurface = TTF_RenderText_Blended(font, musicText.c_str(), musicColor1);
		}

		if (event.motion.x > exitButton.x && event.motion.x < (exitButton.x + exitButton.w) && event.motion.y > exitButton.y && event.motion.y < (exitButton.y + exitButton.h)) {
			/*COLOR HOVER*/
			exitSurface = TTF_RenderText_Blended(font, exitText.c_str(), exitColorH);
		}
		else {/*COLOR NORMAL*/
			exitSurface = TTF_RenderText_Blended(font, exitText.c_str(), exitColor1);
		}



		if (play) {
			if (playH) playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColorH2);
			else
				playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColor2);
			colorChanged = true;
		}
		else if (!play) {
			if (playH) playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColorH1);
			else
				playSurface = TTF_RenderText_Blended(font, playText.c_str(), playColor1);
			colorChanged = false;
		}



		playTexture = SDL_CreateTextureFromSurface(m_renderer, playSurface);
		musicTexture = SDL_CreateTextureFromSurface(m_renderer, musicSurface);
		exitTexture = SDL_CreateTextureFromSurface(m_renderer, exitSurface);


		click = false;

		// DRAW	// NO TIENE QUE HABER IFS NI NADA
		//SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);


		//Buttons
		
		SDL_RenderCopy(m_renderer, playTexture, nullptr, &playButton);
		
		SDL_RenderCopy(m_renderer, musicTexture, nullptr, &musicButton);
		
		SDL_RenderCopy(m_renderer, exitTexture, nullptr, &exitButton);
		
		//Player
		SDL_RenderCopy(m_renderer, playerTexture, &spriteRect, &playerRect);

		//Cursor
		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &cursorRect);

		SDL_RenderPresent(m_renderer);


	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	// SDL_DestroyTexture(cursorTexture); // HAY QUE DESTRUIRLO??
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}



// KEYDOWN Y KEYUP NECESITAN COMPROBAR EL ESTADO ACTUAL Y ANTERIOR DE LA TECLA

// KEYPRESSED ES SIMPLEMENTE SI SE HA PULSADO LA TECLA

// HAY QUE PILLAR EL INPUT CON BOOLS PARA CADA TECLA

// CREAR ELS "UTILS.H" PER DETECTAR LES COLISIONS	bool Collision(punt, recta); (ESTARÍA BIEN CREARNOS LAS CLASES punt Y recta)