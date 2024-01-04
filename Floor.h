#pragma once
#include "SDL2-2.0.10/include/SDL_rect.h"
#include "SDL2-2.0.10/include/SDL_surface.h"

class Floor
{

public:

	SDL_Rect rect;
	static SDL_Surface* image;
	static int floorCount;

	void Init(int x, int y);
	void Draw();
	static void SetFloorImage(SDL_Surface* Image);
};

