#pragma once
#include "SDL2-2.0.10/include/SDL_rect.h"
#include "SDL2-2.0.10/include/SDL_surface.h"
class Ladder
{

public:

	SDL_Rect rect;
	static SDL_Surface* image;
	static int ladderCount;

	void Init(int x, int y);
	void Draw();
	static void SetLadderImage(SDL_Surface* Image);

};

