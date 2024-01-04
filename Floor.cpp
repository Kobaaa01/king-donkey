#include "Renderer.h"
#include "Floor.h"
#include "Constans.h"

int Floor::floorCount = 0;
SDL_Surface* Floor::image = NULL;

void Floor::SetFloorImage(SDL_Surface* Image)
{
	Floor::image = Image;
}

void Floor::Init(int x, int y)
{
	floorCount++;
	rect.x = x;
	rect.y = y;
	rect.w = image->w;
	rect.h = image->h;
}

void Floor::Draw()
{
	 Renderer::DrawSurface(image, rect.x, rect.y);
}
