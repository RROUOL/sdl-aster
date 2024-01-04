#pragma once
#ifndef aSquareFile
#define aSquareFile
#include <iostream>
#include "SDL.h"
#include "Sprite.h"
#include "SZ_Vector2D.h"

// BASE SQUARE

class SZ_Square
{
public:
	SZ_Square();
	~SZ_Square();
	void Init(SDL_Renderer* renderer);
	void Init(SDL_Renderer* renderer, const char* aSpriteLocation,
		int xPosition, int yPosition, 
		int squareWidth, int squareHeight, 
		int colourR, int colourG, int colourB);
	void Update();
	void Render(SDL_Renderer* aRenderer, bool squareDRAWN);
	SDL_Rect rect;
	Sprite sprite;
	int x, y, height, width, R, G, B;

};

// PLAYER SQUARE

class Square_Player: public SZ_Square
{
public:
	int PlayerSpeed;
	int WalkSpeed;
	int RunSpeed;
	Square_Player();
	~Square_Player();
	void Init(SDL_Renderer* renderer);
	void Init(SDL_Renderer* renderer, const char* aSpriteLocation,
		int xPosition, int yPosition, 
		int squareWidth, int squareHeight, 
		int colourR, int colourG, int colourB, 
		int Speed);
	void Input(int whichKey);
	void Update();

	bool isRunning = false;
	bool movingUp = false;
	bool movingLeft = false;
	bool movingDown = false;
	bool movingRight = false;

	bool autoMove = false; 
};

// ENEMY SQUARE

class Square_Enemy : public SZ_Square
{
public:
	int EnemySpeed;
	bool isDead = false;
	int counter = 0;
	int TTL = 1500; // 25 seconds in frames;
	int TTD = 180; // 3 seconds in frames to respawn
	int respawnX = 300; // respawn coords (XY)
	int respawnY = 50;
	int movementType;
	int movingForward = true;
	Square_Enemy();
	~Square_Enemy();
	void Init(SDL_Renderer* renderer);
	void Init(SDL_Renderer* renderer, int xPosition, int yPosition, int squareWidth, int squareHeight, int colourR, int colourG, int colourB, int Speed, int aRX, int aRY, int aM);
	void Update(SDL_Renderer* renderer);
	void Death(SDL_Renderer* renderer);
};

// BULLET SQUARE

class Square_Bullet : public SZ_Square
{
public:
	int BulletSpeed;

	int LifeCounter = 0;

	Square_Bullet();
	~Square_Bullet();
	void Init(SDL_Renderer* renderer);
	void Init(SDL_Renderer* renderer, int xPosition, int yPosition, int squareWidth, int squareHeight, int colourR, int colourG, int colourB, int Speed);
	void Update(SDL_Renderer* renderer);
	SZ_Vector2D velocity; // movement velocity of bullet

	// find the XY difference between Square position and Cursor position
	// then move a fixed speed at that vector
};
#endif