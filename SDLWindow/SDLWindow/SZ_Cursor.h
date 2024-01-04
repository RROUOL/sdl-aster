#pragma once
#include <iostream>
#include "SDL.h"
#include "Sprite.h"
#include "SZ_Vector2D.h"

class SZ_Cursor
{
public:
	SZ_Cursor();
	~SZ_Cursor();
	SDL_Point top, left, right;
	int currentPositionX = -1;
	int currentPositionY = -1;
	int cursorSize;
	int R, G, B, O;
	void Init();
	void Init(int CurSize, int topPos1, int topPos2, int leftPos1, int leftPos2, int rightPos1, int rightPos2, int colourR, int colourG, int colourB, int colourO);
	void updatePos(int posX, int posY);
	void Render(SDL_Renderer* aRenderer);

};

class RO_Cursor
{
public:
	RO_Cursor();
	~RO_Cursor();
	SDL_Point top, left, right;
	Sprite sprite;
	int currentPositionX = -1;
	int currentPositionY = -1;
	int cursorSize = 12;
	int crosshairSize = 36;
	int crosshairPosition = 0;
	int R, G, B, O;
	void Init(SDL_Renderer* renderer, int aR, int aG, int aB, int aO);
	void Init(SDL_Renderer* renderer, int CurSize, int topPos1, int topPos2, int leftPos1, int leftPos2, int rightPos1, int rightPos2, int colourR, int colourG, int colourB, int colourO);
	void updatePos(int posX, int posY);
	void Render(SDL_Renderer* aRenderer);
};