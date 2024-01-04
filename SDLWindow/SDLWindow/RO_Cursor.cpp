#include "SZ_Cursor.h"

RO_Cursor::RO_Cursor()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cursor Constructed with Param(%p)", this);
	sprite.~Sprite();
}

RO_Cursor::~RO_Cursor()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cursor Destroyed with Param(%p)", this);
	sprite.~Sprite();
}

SDL_Point top, left, right;

int currentPositionX = -1;
int currentPositionY = -1;
int cursorSize;

void RO_Cursor::Init(SDL_Renderer* renderer, int aR, int aG, int aB, int aO)
{
	top = { 0,10 }, left = { -10, -10 }, right = { 10, -10 };

	R = aR;
	G = aG;
	B = aB;
	O = aO;

	cursorSize = 12;
	crosshairSize = 36;
	crosshairPosition = -(crosshairSize / 2);

	sprite.Init(
		renderer, // output renderer
		crosshairPosition, crosshairPosition,	// XY position where sprite will appear
		crosshairSize, crosshairSize,		// XY size of sprite
		"content/sprites/crosshair.png", // where sprite is located
		1, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		false, // is this sprite animated?
		1,
		R, G, B, O); // if animated, how many sprites does it go through per second?

	sprite.SetColour(R, G, B, O);
}

void RO_Cursor::Init(SDL_Renderer* renderer, int CurSize, int topPos1, int topPos2, int leftPos1, int leftPos2, int rightPos1, int rightPos2, int colourR, int colourG, int colourB, int colourO)
{
	cursorSize = CurSize;

	top = { topPos1, topPos2 };
	left = { leftPos1, leftPos2 };
	right = { rightPos1, rightPos2 };

	R = colourR;
	G = colourG;
	B = colourB;
	O = colourO;

	crosshairSize = (cursorSize * 3);
	crosshairPosition = -(crosshairSize / 2);

	sprite.Init(
		renderer, // output renderer
		crosshairPosition, crosshairPosition,	// XY position where sprite will appear
		crosshairSize, crosshairSize,		// XY size of sprite
		"content/sprites/crosshair.png", // where sprite is located
		1, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		false, // is this sprite animated?
		1,
		R, G, B, O); // if animated, how many sprites does it go through per second?

	sprite.SetColour(R, G, B, O);
}

void RO_Cursor::updatePos(int posX, int posY)
{
	currentPositionX = posX;
	currentPositionY = posY;
	//top = { posX, posY - cursorSize }, left = { posX - cursorSize, posY + cursorSize }, right = { posX + cursorSize, posY + cursorSize };

	sprite.Update(posX + crosshairPosition, posY + crosshairPosition);

	//sprite.SetOpacity(O);
}

void RO_Cursor::Render
(SDL_Renderer* aRenderer)
{
	SDL_SetRenderDrawColor(aRenderer, R, G, B, O);

	//if (cursorDRAWN)
	//{
	//	SDL_RenderDrawLine(aRenderer, top.x, top.y, left.x, left.y);
	//	SDL_RenderDrawLine(aRenderer, top.x, top.y, right.x, right.y);
	//	SDL_RenderDrawLine(aRenderer, left.x, left.y, right.x, right.y);
	//}
	

	sprite.Render(aRenderer);
}