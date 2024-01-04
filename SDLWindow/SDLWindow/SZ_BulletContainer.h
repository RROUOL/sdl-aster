#ifndef aBulletContainerFILE
#define aBulletContainerFILE

#include <vector>
#include <iostream>
#include "SDL.h"
#include "SZ_Square.h"

using namespace std;

class SZ_BulletContainer
{
public:
	SZ_BulletContainer();
	~SZ_BulletContainer();
	void Init(SDL_Renderer* renderer, int eY, int eX, int eNum, int TTL);
	void Add(SDL_Renderer* renderer, int X, int Y);
	void Input(SDL_Renderer* renderer, int playerX, int playerY, int cursorX, int cursorY);
	void Render(SDL_Renderer* aRenderer, bool squareDRAWN);
	void Update(SDL_Renderer* renderer);
	vector<Square_Bullet*> aListofBullets;

	void Shoot(); // if able, it sends a bullet downwards
	int X, Y, Num; // position and max bullets it can spawn
	// position should be out-of-bounds so enemies cannot be killed by deactivated bullets
	int TTL = 60; // time to live of Bullets
	SDL_Rect aRect;
};
#endif 
