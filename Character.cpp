#include "Character.h"
#include "Renderer.h"

void Character::Init(int x, int y)
{
	rect.x = x;
	rect.y = y;
	rect.w = image->w;
	rect.h = image->h;
}

void Character::Draw()
{
	Renderer::DrawSurface(image, rect.x, rect.y);
}

void Character::Move(Direction direction)
{
	float calculatedSpeed = speed * Renderer::deltaTime;
	switch (direction)
	{
	case Direction::Left:
		rect.x -= calculatedSpeed;
		break;
	case Direction::Right:
		rect.x += calculatedSpeed;
		break;
	case Direction::Up:
		rect.y -= calculatedSpeed;
		break;
	case Direction::Down:
		rect.y += calculatedSpeed;
		break;
	}
}

bool Character::isColliding(SDL_Rect &other)
{
	SDL_Rect intCharacterRect = { rect.x, rect.y, rect.w, rect.h }; // temporary rect, because characer Rect is FRect (float version)
	return SDL_HasIntersection(&intCharacterRect, &other);
}
