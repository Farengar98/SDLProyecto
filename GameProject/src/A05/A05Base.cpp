/*#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>

#include "Collisions.h"

//Game general information
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#define FPS 60

int main(int, char*[]) {

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags))throw "Error al carregar!";
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error:SDL_mixer init";

	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10;
	float deltaTime = 0;

	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// --- SPRITES ---
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bgCastle.jpg") };
	if (bgTexture == nullptr)throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/kintoun.png") };
	//if (playerTexture == nullptr) throw "Nos'han pogut crear les textures";
	//SDL_Rect playerRect{ 0, 0, 350, 189 };
	SDL_Rect playerTarget{ 0, 0, 100, 100 };
	// --- Animated Sprite ---

	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	SDL_Rect playerRect, playerPosition;
	SDL_Rect mapWalls;
	int top = 180;
	mapWalls.x = 0;
	mapWalls.y = top;
	mapWalls.w = SCREEN_WIDTH;
	mapWalls.h = SCREEN_HEIGHT - top;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;
	playerPosition.x = playerPosition.y = 0;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;

	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 80) };
	if (font == nullptr) throw "No es pot iicialitzar the TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{ 255, 150, 0, 255 }) };
	if (tmpSurf == nullptr) TTF_CloseFont(font), throw "Unable to create the SDL text surface";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textRect{ 100, 50, tmpSurf->w, tmpSurf->h };
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);

	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	playerPosition.x = SCREEN_WIDTH / 3;
	playerPosition.y = 2 * SCREEN_HEIGHT / 3;
	bool Wdown = false;
	bool Adown = false;
	bool Sdown = false;
	bool Ddown = false;

	int velocidad = 4;

		// ESTO NO VA 
	bool Wup = true;
	bool Aup = true;
	bool Sup = true;
	bool Dup = true;
	


	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		isRunning = false; break;
			case SDL_MOUSEMOTION:
				//playerRect.x = event.motion.x; 
				//playerRect.y = event.motion.y;
				playerTarget.x = event.motion.x - 50;
				playerTarget.y = event.motion.y - 50;
				break;
			case SDL_KEYDOWN:

				if (event.key.keysym.sym == SDLK_ESCAPE)	isRunning = false;

				if (event.key.keysym.sym == SDLK_w) {
					std::cout << "W pulsada" << std::endl;
					Wdown = true;
				}
				if (event.key.keysym.sym == SDLK_a) {
					std::cout << "A pulsada" << std::endl;
					Adown = true;
				}
				if (event.key.keysym.sym == SDLK_s) {
					std::cout << "S pulsada" << std::endl;
					Sdown = true;
				}
				if (event.key.keysym.sym == SDLK_d) {
					std::cout << "D pulsada" << std::endl;
					Ddown = true;
				}
				break;

			case SDL_KEYUP:

				if (event.key.keysym.sym == SDLK_s)
				{
					Sdown = false;
					std::cout << "S levantada" << std::endl;
				}
					

				if (event.key.keysym.sym == SDLK_w)
				{
					Wdown = false;
					std::cout << "W levantada" << std::endl;
				}
					

				if (event.key.keysym.sym == SDLK_a) 
				{
					Adown = false;
					std::cout << "A levantada" << std::endl;
				}
					

				if (event.key.keysym.sym == SDLK_d)
				{
					Ddown = false;
					std::cout << "D levantada" << std::endl;
				}
					

				break;
				
			default:
				break;
			}
		}

		// UPDATE

		//playerRect.x += (playerTarget.x - playerRect.x) / 10;
		//playerRect.y += (playerTarget.y - playerRect.y) / 10;


		if (Wdown && !Collisions::OnCollisionWalls(playerPosition, mapWalls))
		{
			playerPosition.y += -velocidad;
		}
		if (Adown && !Collisions::OnCollisionWalls(playerPosition, mapWalls))
		{
			playerPosition.x += -velocidad;
		}
		if (Sdown && !Collisions::OnCollisionWalls(playerPosition, mapWalls))
		{
			playerPosition.y += velocidad;
		}
		if (Ddown && !Collisions::OnCollisionWalls(playerPosition, mapWalls))
		{
			playerPosition.x += velocidad;
		}
		


		


		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;

		if(deltaTime)

		frameTime++;
		if (FPS / frameTime <= 9)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x == 3 * frameWidth)
				playerRect.x = 0;
		}


		// DRAW
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
		//Background

		//Animated Sprite
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderPresent(renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// --- QUIT ---
	Mix_CloseAudio();

	IMG_Quit();
	TTF_Quit();
	Mix_Quit;

	SDL_Quit();
	return 0;
}
*/


#include <stdlib.h>
#include <time.h>
#include "Game.h"

int main()
{
	srand(time(NULL));

	Game game;
	game.Run();
	return 0;
}