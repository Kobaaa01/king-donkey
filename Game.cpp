#include "Game.h"
#include <stdio.h>
#include <process.h>
#include "Ladder.h"
#include "SDL2-2.0.10/include/SDL_events.h"

void Game::Init()
{
	LoadImages();
	createFloor();
	createLadder();
	int startingPlayerX = SCREEN_WIDTH / 6;
	int startingPlayerY = SCREEN_HEIGHT / 2 - character.image->h/2;
	character.Init(startingPlayerX, startingPlayerY);
	restart = false;
}

void Game::LoadImages()
{
	SDL_Surface* floorImage = SDL_LoadBMP("floor.bmp");
	if (floorImage == NULL)
	{
		printf("SDL_LoadBMP(floor.bmp) error: %s\n", SDL_GetError());
		exit(1);
	}
	Floor::SetFloorImage(floorImage);
	Floor::floorCount = 0;

	SDL_Surface* ladderImage = SDL_LoadBMP("ladder.bmp");
	if (ladderImage == NULL)
	{
		printf("SDL_LoadBMP(ladder.bmp) error: %s\n", SDL_GetError());
		exit(1);
	}
	Ladder::SetLadderImage(ladderImage);
	Ladder::ladderCount = 0;

	SDL_Surface* characterImage = SDL_LoadBMP("character.bmp");
	if (characterImage == NULL)
	{
		printf("SDL_LoadBMP(character.bmp) error: %s\n", SDL_GetError());
		exit(1);
	}
	character.image = characterImage;
}

void Game::DestroyImages()
{
	SDL_FreeSurface(Floor::image);
	SDL_FreeSurface(Ladder::image);
	SDL_FreeSurface(character.image);
}

void Game::Update()
{
	HandleInput();
	applyGravity();
	DrawAll();
}

void Game::DrawAll()
{
	drawFloor();
	drawLadder();
	character.Draw();
}

void Game::HandleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				exit(0);
			}
			else if (event.key.keysym.sym == SDLK_n) //nowa gra
			{
				restart = true;
			}
			break;
		case SDL_QUIT:
			exit(0);
			break;
		};
	};

	// more frequent input handling
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		if (character.rect.x > 0 + character.rect.w / 2)
		{
			character.Move(Direction::Left);
		}
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		if (character.rect.x < SCREEN_WIDTH - character.rect.w/2)
		{
			character.Move(Direction::Right);
		}
	}
	else if (keyboardState[SDL_SCANCODE_UP])
	{
		if (isChracterOnLadder())
		{
			character.Move(Direction::Up);
		}
	}
	else if (keyboardState[SDL_SCANCODE_DOWN])
	{
		if (isChracterOnLadder() && !isCharacterClippingTroughGround())
		{
			character.Move(Direction::Down);
		}
	}

}

void Game::createFloor()
{

	// ground floor
	floors[Floor::floorCount].Init(0, 0);
	for (int i = -1; i < SCREEN_WIDTH / Floor::image->w; i++)
	{
		int x = COORDINATE_ZERO + (i + 2) * Floor::image->w - Floor::image->w / 2;
		int y = SCREEN_HEIGHT;
		floors[Floor::floorCount].Init(x, y);
	}

//first floor

	//left side
	for (int i = 1; i <= 3; i++)
	{
		int x = COORDINATE_ZERO + i * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 3;
		floors[Floor::floorCount].Init(x, y);
	}
	//right side
	for (int i = 1; i <= 3; i++)
	{
		int x = SCREEN_WIDTH - i * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 3;
		floors[Floor::floorCount].Init(x, y);
	}
//second floor

	//right side
	for (int i = 1; i <= 8; i++)
	{
		int x = SCREEN_WIDTH - i * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 6;
		floors[Floor::floorCount].Init(x, y);
	}

	//left side
	for (int i = 1; i <= 4; i++)
	{
		int x = COORDINATE_ZERO + i * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 6;
		floors[Floor::floorCount].Init(x, y);
	}

//third floor

	for (int i = 3; i <= 6; i++)
	{
		int x = SCREEN_WIDTH - i * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 9;
		floors[Floor::floorCount].Init(x, y);
	}

//fourth floor

	for (int i = 0; i < TOP_BLOCKS; i++)
	{
		int x = COORDINATE_ZERO + (i + 2) * Floor::image->w;
		int y = SCREEN_HEIGHT - Floor::image->h * 12;
		floors[Floor::floorCount].Init(x, y);
	}

}

void Game::createLadder()
{
//first floor

	//left side
	for (int i = 1; i <= 3; i++)
	{
		int x = COORDINATE_ZERO + 2 * Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}
	//right side
	for (int i = 1; i <= 3; i++)
	{
		int x = SCREEN_WIDTH - 2 * Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}

//second floor

	//right side
	for (int i = 4; i <= 6; i++)
	{
		int x = SCREEN_WIDTH - 3 * Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}

	//left side
	for (int i = 4; i <= 6; i++)
	{
		int x = COORDINATE_ZERO + Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}

//third floor

	for (int i = 7; i <= 9; i++)
	{
		int x = SCREEN_WIDTH - 6 * Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}

//fourth floor

	for (int i = 10; i <= 12; i++)
	{
		int x = SCREEN_WIDTH - 4 * Ladder::image->w;
		int y = SCREEN_HEIGHT - Ladder::image->h * i;
		ladders[Ladder::ladderCount].Init(x, y);
	}

}

void Game::drawFloor()
{
	for (int i = 0; i < Floor::floorCount; i++)
	{
		floors[i].Draw();
	}
}

void Game::drawLadder()
{
	for (int i = 0; i < Ladder::ladderCount; i++)
	{
		ladders[i].Draw();
	}
}

void Game::applyGravity()
{
	if (!isChracterOnLadder())
	{
		character.rect.y += 1;
		for (int i = 0; i < Floor::floorCount; i++)
		{
			if (character.isColliding(floors[i].rect))
			{
				character.rect.y -= 1;
			}
		}
	}
}

bool Game::isChracterOnLadder()
{
	for (int i = 0; i < Ladder::ladderCount; i++)
	{
		if (character.isColliding(ladders[i].rect))
		{
			return true;
		}
	}
	return false;
}

bool Game::isCharacterClippingTroughGround()
{
	// offseting character rect to check in easy way if its foot is touching ground
	SDL_Rect offsetedCharacterRect = { character.rect.x, character.rect.y + character.rect.h, character.rect.w, character.rect.h };
	for (int i = 0; i < Ladder::ladderCount; i++)
	{
		if (SDL_HasIntersection(&offsetedCharacterRect, &ladders[i].rect))
		{
			return false;
		}
	}
	return true;
}