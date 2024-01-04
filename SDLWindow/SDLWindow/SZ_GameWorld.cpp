#include "SZ_GameWorld.h"

SZ_GameWorld::~SZ_GameWorld()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Scene Destroyed with Param(%p)", this);
}

void SZ_GameWorld::run() {}

bool SZ_GameWorld::toggleFullScreen(SDL_Window* window, SDL_Renderer* renderer, bool currentState) // toggle fullscreen
{
	currentState = !currentState;
	if (currentState)
	{
		SDL_RenderSetLogicalSize(renderer, 800, 600);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, 800, 600);
	}

	SDL_RenderPresent(renderer);

	SDL_SetWindowFullscreen(window, currentState);

	return currentState;
}

bool SZ_GameWorld::checkCollision(SDL_Rect A, SDL_Rect B)
{ // checkCollision() function retrieved from "https://stackoverflow.com/questions/9487793/collisions-in-sdl-c"
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void SZ_GameWorld::init(
	char aPlayerE, int aPlayerR, int aPlayerG, int aPlayerB, int aPlayerO, // player
	int aCursorR, int aCursorG, int aCursorB, int aCursorO, // cursor
	int aBGR, int aBGG, int aBGB // background colour
)
{
	pE = aPlayerE;
	pR = aPlayerR;
	pG = aPlayerG;
	pB = aPlayerB;
	pO = aPlayerO;

	cursorR = aCursorR;
	cursorG = aCursorG;
	cursorB = aCursorB;
	cursorO = aCursorO;

	bgR = aBGR;
	bgG = aBGG;
	bgB = aBGB;
}