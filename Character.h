#pragma once
#include "SDL2-2.0.10/include/SDL_rect.h"
#include "SDL2-2.0.10/include/SDL_surface.h"
#include "Constans.h"

enum class Direction
{
	Left,
	Right,
	Up,
	Down
};

class Character
{
public:

	int speed = PLAYER_SPEED;
	SDL_FRect rect;
	SDL_Surface* image;

	void Init(int x, int y);
	void Draw();
	void Move(Direction direction);
	bool isColliding(SDL_Rect &rect);
};

