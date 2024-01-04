#include "Sprite.h"
#include "SZ_Timer.h"

Sprite::Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Constructed with Param(%p)", this);
	IMG_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
}

Sprite::~Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Destroyed with Param(%p)", this);
}

void Sprite::Init(SDL_Renderer* aRenderer) // default Init
{
	//std::cout << this << ".Sprite::Init() called" << std::endl;

	SDL_Surface* surface;
	surface = IMG_Load("content/sprites/sprite.png");
	if (!surface) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}

	isAnimated = false;
	canXFlip = false;
	canYFlip = false;

	spritePosition.x = spritePosition.y = 0;
	spritePosition.w = spritePosition.h = 32;
	frameWidth = 1;
	frameHeight = 1;

	spritesPerSecond = 4;

	//Convert to a texture
	currentImage = SDL_CreateTextureFromSurface(aRenderer, surface);
	//Free up the surface data from RAM
	SDL_FreeSurface(surface);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight); // saves the width/height of the texture

	frameWidth = textureWidth / sheetWidth;
	frameHeight = textureHeight / sheetHeight;

	spriteRect.x = xPosition = 0;
	spriteRect.y = yPosition = 0;
	spriteRect.w = frameWidth;
	spriteRect.h = frameHeight;

	SetColour(255, 255, 255, 255);
	SDL_RenderCopy(aRenderer, currentImage, &spriteRect, &spritePosition);


}

void Sprite::Init(SDL_Renderer* aRenderer,
	int aXPosition, int aYPosition,
	int aWPosition, int aHPosition,
	const char* aSpriteLocation,
	int aSheetWidth, int aSheetHeight,
	bool aCanXFlip, bool aCanYFlip,
	bool aIsAnimated, int aSpritesPerSecond,
	int aRed, int aGreen, int aBlue, int aOpacity)
{
	//std::cout << this << ".Sprite::Init(extra) called" << std::endl;

	//spriteRect = aSpriteRect;

	xPosition = aXPosition;
	yPosition = aYPosition;
	wPosition = aWPosition;
	hPosition = aHPosition;

	spriteLocation = aSpriteLocation;

	sheetWidth = aSheetWidth;
	sheetHeight = aSheetHeight;

	canXFlip = aCanXFlip;
	canYFlip = aCanYFlip;

	isAnimated = aIsAnimated;
	spritesPerSecond = aSpritesPerSecond;

	SDL_Surface* surface;
	surface = IMG_Load(spriteLocation);
	if (!surface) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}

	//Convert to a texture
	currentImage = SDL_CreateTextureFromSurface(aRenderer, surface);
	//Free up the surface data from RAM
	SDL_FreeSurface(surface);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight); // saves the width/height of the texture

	frameWidth = textureWidth / sheetWidth;
	frameHeight = textureHeight / sheetHeight;

	spriteRect.x = spriteRect.y = 0;

	spriteRect.w = frameWidth;
	spriteRect.h = frameHeight;

	spritePosition.x = xPosition;
	spritePosition.y = yPosition;

	spritePosition.w = wPosition;
	spritePosition.h = hPosition;

	SetColour(255, 255, 255, 255);

	SDL_RenderCopy(aRenderer, currentImage, &spriteRect, &spritePosition);
}

void Sprite::Render(SDL_Renderer* aRenderer)
{
	//std::cout << this << ".Sprite::Render() called" << std::endl;

	SDL_RenderCopy(aRenderer, currentImage, &spriteRect, &spritePosition);
}

void Sprite::Update()
{
	//std::cout << this << ".Sprite::Update() called" << std::endl;

	// update position change..
	// (...)

	// if canXFlip, if canYFlip

	if (!isAnimated) // if not animated, stop here
	{
		return;
	}
	else // if animated, go
	{
		frameTime++;

		if (FPS / frameTime == spritesPerSecond)
		{
			frameTime = 0;
			spriteRect.x += frameWidth;
			if (spriteRect.x >= textureWidth)
			{
				spriteRect.x = 0;
			}
		}
	}
}

void Sprite::Update(int aXPosition, int aYPosition)
{
	//std::cout << this << ".Sprite::Update() called" << std::endl;

	// update position change..
	xPosition = aXPosition;
	yPosition = aYPosition;

	spritePosition.x = xPosition;
	spritePosition.y = yPosition;

	// if canXFlip, if canYFlip

	if (!isAnimated) // if not animated, stop here
	{
		return;
	}
	else // if animated, go
	{
		frameTime++;

		if (FPS / frameTime == spritesPerSecond)
		{
			frameTime = 0;
			spriteRect.x += frameWidth;
			if (spriteRect.x >= textureWidth)
			{
				spriteRect.x = 0;
			}
		}
	}
}

void Sprite::SetColour(int aRed, int aGreen, int aBlue, int aAlpha)
{
	SDL_SetTextureColorMod(currentImage, aRed, aGreen, aBlue);
	SDL_SetTextureAlphaMod(currentImage, aAlpha);
}