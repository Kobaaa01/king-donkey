#include "Renderer.h"
#include "Ladder.h"
#include "Constans.h"

int Ladder::ladderCount = 0;
SDL_Surface* Ladder::image = NULL;

void Ladder::SetLadderImage(SDL_Surface* Image)
{
	Ladder::image = Image;
}

void Ladder::Init(int x, int y)
{
	ladderCount++;
	rect.x = x;
	rect.y = y - 1; // -1 to make player able to climb down
	rect.w = image->w;
	rect.h = image->h + 1;
}

void Ladder::Draw()
{
	Renderer::DrawSurface(image, rect.x, rect.y);
}
