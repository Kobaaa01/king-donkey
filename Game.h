#pragma once
#include "Floor.h"
#include "Constans.h"
#include "Ladder.h"
#include "Character.h"

class Game
{

public:

	bool restart;
	Floor floors[128];
	Ladder ladders[128];
	Character character;

	void Init();
	void LoadImages();
	void DestroyImages();
	void Update();
	void DrawAll();
	void HandleInput();

	void createFloor();
	void createLadder();

	void drawFloor();
	void drawLadder();

	void applyGravity();

	bool isChracterOnLadder();

	bool isCharacterClippingTroughGround();

};

