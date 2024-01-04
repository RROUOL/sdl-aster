#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

class Sprite
{
private:
	const int FPS = 1000 / 17; // 60 FPS
	int frameTime = 0; // countdown for when sprite changes (if animated)
	bool canXFlip, canYFlip; // is able to flip on the X and/or Y axis
	int sheetWidth = 1; // how many sprites per row (1 if no sheet)
	int sheetHeight = 1; // how many sprites per column (1 if no sheet)

	int textureWidth, textureHeight; // automatically calculated

	int frameWidth, frameHeight; // = (textureSize / sheetSize);
	
	const char* spriteLocation; // location of the sprite in text format
	SDL_Texture* currentImage;

public:
	Sprite();
	~Sprite();
	SDL_Rect spriteRect; // srcRect
	SDL_Rect spritePosition; // dstRect
	int xPosition, yPosition; // XY coords of sprite
	int wPosition, hPosition; // XY size of sprite

	bool isAnimated; // whether or not the sprite is currently animating
	int spritesPerSecond; // if animated, how many times the sprite changes per second

	bool isXFlipped, isYFlipped = false; // is currently flipped on the X and/or Y axis;

	void Init(SDL_Renderer* renderer); // default initialisation
	void Init(
		SDL_Renderer* renderer,	// renderer,
		int aXPosition, // spritePosition.x,
		int aYPosition, // spritePosition.y,
		int aWPosition, // spritePosition.w,
		int aHPosition, // spritePosition.h,
		const char* aSpriteLocation, // sprite location,
		int aSheetWidth, // sheetWidth,
		int aSheetHeight, // sheetHeight,
		bool aCanXFlip, // canXFlip,
		bool aCanYFlip,  // canYFlip,
		bool aIsAnimated, // isAnimated,
		int aSpritesPerSecond, // spritesPerSecond
		int aRed, int aGreen, int aBlue, int aOpacity
		);
	    


	void Render(SDL_Renderer* aRenderer);
	void Update();
	void Update(int aXPosition, int aYPosition); // Update which changes sprite position

	void FlipX();
	void FlipY();

	void SetColour(int aRed, int aGreen, int aBlue, int aAlpha);

};
