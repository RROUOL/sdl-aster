#include "SZ_GameContainerSquare.h"

SZ_GameContainerSquare::SZ_GameContainerSquare()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Container Constructed with Param(%p)", this);
}

SZ_GameContainerSquare::~SZ_GameContainerSquare() {
	for (auto& element : aListofSquares)
	{
		delete element;

	}
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Container Destroyed with Param(%p)", this);
}
void SZ_GameContainerSquare::Init(SDL_Renderer* renderer,
	const char* aSpriteLocation,
	int eX, int eY,
	float eDirX, float eDirY, 
	int eNum)
{
	X = eX;
	Y = eY;
	dirX = eDirX;
	dirY = eDirY;
	Num = eNum;
	for (int i = 0; i < Num; i++)
	{
		int PosX = X + (i * (dirX * 50));
		int PosY = Y + (i * (dirY * 50));
		Add(renderer, aSpriteLocation, PosX, PosY);
	}
}

void SZ_GameContainerSquare::Add(SDL_Renderer* renderer, const char* aSpriteLocation,
	int X, int Y)
{
	SZ_Square* aSquare = new SZ_Square();
	aSquare->Init(renderer, aSpriteLocation, X, Y, 50, 50, 255, 255, 255);
	this->aListofSquares.push_back(aSquare);
}

void SZ_GameContainerSquare::Render(SDL_Renderer* aRenderer, bool squareDRAWN)
{
	for (auto& element : aListofSquares)
	{
		element->Render(aRenderer, squareDRAWN);
	}
}

void SZ_GameContainerSquare::Update()
{
}

