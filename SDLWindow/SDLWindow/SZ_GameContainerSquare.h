#ifndef aGameContainerSquareFILE
#define aGameContainerSquareFILE

#include <vector>
#include <iostream>
#include "SDL.h"
#include "SZ_Square.h"

using namespace std;

class SZ_GameContainerSquare
{
public:
	SZ_GameContainerSquare();
	~SZ_GameContainerSquare();
	void Init(SDL_Renderer* renderer,
		const char* aSpriteLocation, 
		int eX, int eY, 
		float eDirX, float eDirY, 
		int eNum);
	void Add(SDL_Renderer* renderer,
		const char* aSpriteLocation,
		int X, int Y);
	void Render(SDL_Renderer* aRenderer, bool squareDRAWN);
	void Update();
	vector<SZ_Square*> aListofSquares;
	int X, Y, Num;
	float dirX, dirY;
};

#endif //
