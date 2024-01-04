#pragma once
#ifndef aGameWorldFILE
#define aGameWorldFILE

#include <iostream>
#include "stdio.h";
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "SZ_Timer.h"
#include "SZ_Cursor.h"
#include "SZ_Square.h"
#include "SZ_GameContainerSquare.h"
#include "Sprite.h"
#include "SZ_BulletContainer.h"


#define MAX_KEYS (256)
#define MOVE_LEFT 'w'


class SZ_GameWorld
{

protected:
	TTF_Font* pixelFont;
	SZ_Timer aTimer;
	bool done = false;
	
	// read from specs.txt:
	char pE ='N';
	int pR, pG, pB, pO = 255;
	int cursorR, cursorG, cursorB, cursorO = 255;
	int bgR, bgG, bgB = 0;

	
public:
	~SZ_GameWorld();
	//SDL_Window* window;
	//SDL_Renderer* renderer;
	SDL_Event _event;

	int R;
	int G;
	int B = 20;
	bool isIncreasing = true;

	int frameCounter = 0; // counts amount of frames
	int MouseMoveCounter = 0;
	int mousePosX, mousePosY;
	Uint32 mousePosition; // tracks mouse position
	const Uint8* keystate; // tracks what keys are pressed
	const Uint8* mousestate; // tracks clicks

	bool gKeys[MAX_KEYS];

	virtual void run();

	bool toggleFullScreen(SDL_Window* window, SDL_Renderer* renderer, bool currentState);
	/*
	bool checkCollision(
		int up1, int down1,
		int rectW1, int rectH1,
		int rectX2, int rectY2,
		int rectW2, int rectH2);
	*/

	bool checkCollision(
		SDL_Rect A, SDL_Rect B);

	void init(
		char aPlayerE, int aPlayerR, int aPlayerG, int aPlayerB, int aPlayerO, // player
		int aCursorR, int aCursorG, int aCursorB, int aCursorO, // cursor
		int aBGR, int aBGG, int aBGB // background colour
	); // keeps track of player decisions
};

class SplashScreen: public SZ_GameWorld
{
public:
	//SZ_Gameworld();
	~SplashScreen();
	void run(SDL_Window* window, SDL_Renderer* renderer);

	// sprites
	Sprite asterLogo;
	Sprite astie;
	Sprite controls;

	// mouse
	RO_Cursor playerCursor;
	// mouse trail
	RO_Cursor cursorTrail_1;
	RO_Cursor cursorTrail_2;
	RO_Cursor cursorTrail_3;
	RO_Cursor cursorTrail_4;

	
};

class GameScreen : public SZ_GameWorld
{
private:
	bool shootButtonPressed = false;
public:
	//SZ_Gameworld();
	~GameScreen();
	int run(SDL_Window* window, SDL_Renderer* renderer);

	bool CheckForCollisions(
		int rectX1, int rectY1,
		int rectW1, int rectH1,
		int rectX2, int rectY2,
		int rectW2, int rectH2);

	// mouse
	RO_Cursor playerCursor;
	// mouse trail
	RO_Cursor cursorTrail_1;
	RO_Cursor cursorTrail_2;
	RO_Cursor cursorTrail_3;
	RO_Cursor cursorTrail_4;
	// square
	SZ_Square collisionBlock;
	//square player
	Square_Player playerSquare;
	// square containers
	SZ_GameContainerSquare leftWallContainerSquare;
	SZ_GameContainerSquare rightWallContainerSquare;
	SZ_GameContainerSquare downWallContainerSquare;
	// square enemies
	Square_Enemy enemy1;
	Square_Enemy enemy2;
	Square_Enemy enemy3;
	// square bullet container
	SZ_BulletContainer aBulletContainer;
};

class EndScreen : public SZ_GameWorld
{
public:
	//SZ_Gameworld();
	~EndScreen();

	void run(SDL_Window* window, SDL_Renderer* renderer, int score);

	// sprites
	Sprite asterLogo;
	Sprite gameOver;

	// mouse
	RO_Cursor playerCursor;
	// mouse trail
	RO_Cursor cursorTrail_1;
	RO_Cursor cursorTrail_2;
	RO_Cursor cursorTrail_3;
	RO_Cursor cursorTrail_4;
};
#endif