#include "SZ_Cursor.h"

SZ_Cursor::SZ_Cursor()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cursor Constructed with Param(%p)", this);
}

SZ_Cursor::~SZ_Cursor()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cursor Destroyed with Param(%p)", this);
}
/*
SDL_Point top, left, right;

int currentPositionX = -1;
int currentPositionY = -1;
int cursorSize;
*/
void SZ_Cursor::Init()
{
	top = { 0,10 }, left = { -10, -10 }, right = { 10, -10 };

	R = 255;
	G = 255;
	B = 0;
	O = 204;

	cursorSize = 12;
}

void SZ_Cursor::Init(int CurSize, int topPos1, int topPos2, int leftPos1, int leftPos2, int rightPos1, int rightPos2, int colourR, int colourG, int colourB, int colourO)
{
	cursorSize = CurSize;

	top = { topPos1, topPos2 };
	left = { leftPos1, leftPos2 };
	right = { rightPos1, rightPos2 };

	R = colourR;
	G = colourG;
	B = colourB;
	O = colourO;
}

void SZ_Cursor::updatePos(int posX, int posY)
{
	currentPositionX = posX;
	currentPositionY = posY;
	top = { posX, posY - cursorSize }, left = { posX - cursorSize, posY + cursorSize }, right = { posX + cursorSize, posY + cursorSize };
}

void SZ_Cursor::Render
(SDL_Renderer* aRenderer)
{
	SDL_SetRenderDrawColor(aRenderer, R, G, B, O);

	SDL_RenderDrawLine(aRenderer, top.x, top.y, left.x, left.y);
	SDL_RenderDrawLine(aRenderer, top.x, top.y, right.x, right.y);
	SDL_RenderDrawLine(aRenderer, left.x, left.y, right.x, right.y);
}

