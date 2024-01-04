#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Renderer.h"
#include "Constans.h"
#include "Game.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

/* anchor of any image starts in the middle because of how DrawSurface is implemented */
/* anchor of any collider starts in the top left corner */

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	Game* game;
	int t1, t2, quit, frames, rc;
	double worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Surface* charset, * floor_block, * character, * ladder;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Jakub Kwiatkowski, s198074");



	Renderer::Init();
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	// SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(Renderer::screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	char text[128];
	int czarny = SDL_MapRGB(Renderer::screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(Renderer::screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(Renderer::screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(Renderer::screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	distance = 0;
	etiSpeed = 1;

	while (true)
	{
		game = new Game();
		game->Init();
		worldTime = 0;

		while (!game->restart) {
			t2 = SDL_GetTicks();

			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplyna³ od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			// here t2-t1 is the time in milliseconds since
			// the last screen was drawn
			// delta is the same time in seconds
			Renderer::deltaTime = (t2 - t1) * 0.001;
			t1 = t2;
			worldTime += Renderer::deltaTime;
			distance += etiSpeed * Renderer::deltaTime;
			SDL_FillRect(Renderer::screen, NULL, zielony);

			// UPDATING THE GAME
			game->Update();

			fpsTimer += Renderer::deltaTime;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			// tekst informacyjny / info text
			Renderer::DrawRectangle(4, 4, SCREEN_WIDTH - 8, 36, czarny, niebieski);
			//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
			sprintf(text, "King Donkey by Jakub, time = %.1lf s  %.0lf fps", worldTime, fps);
			Renderer::DrawString(Renderer::screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			//	      "Esc - exit, \030 - faster, \031 - slower"
			sprintf(text, "Esc - exit | n - new game");
			Renderer::DrawString(Renderer::screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			SDL_UpdateTexture(scrtex, NULL, Renderer::screen->pixels, Renderer::screen->pitch);
			//		SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
			
			frames++;
		};
		delete game;
	}

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(Renderer::screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(floor_block);
	SDL_FreeSurface(ladder);
	SDL_FreeSurface(character);

	SDL_Quit();
	return 0;
};
