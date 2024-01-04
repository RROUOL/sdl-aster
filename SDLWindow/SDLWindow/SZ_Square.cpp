#include "SZ_Square.h"

// BASE SQUARE

SZ_Square::SZ_Square()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Constructed with Param(%p)", this);
}

SZ_Square::~SZ_Square()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Destroyed with Param(%p)", this);
}

void SZ_Square::Init(SDL_Renderer* renderer)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 32;
	rect.h = 32;

	R = 255;
	G = 255;
	B = 255;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/spritesheet.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void SZ_Square::Init(SDL_Renderer* renderer, const char* aSpriteLocation, 
	int xPosition, int yPosition, 
	int squareWidth, int squareHeight, 
	int colourR, int colourG, int colourB)
{
	rect.x = xPosition;
	rect.y = yPosition;
	rect.w = squareWidth;
	rect.h = squareHeight;

	R = colourR;
	G = colourG;
	B = colourB;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		aSpriteLocation, // where sprite is located
		1, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void SZ_Square::Update() 
{
	sprite.Update(rect.x, rect.y);
}

void SZ_Square::Render
(SDL_Renderer * aRenderer, bool squareDRAWN)
{
	if (squareDRAWN)
	{
		SDL_SetRenderDrawColor(aRenderer, R, G, B, 255);
		SDL_RenderDrawRect(aRenderer, &rect);
	}
	sprite.Render(aRenderer);
}

// PLAYER SQUARE

Square_Player::Square_Player()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player Constructed with Param(%p)", this);
}

Square_Player::~Square_Player()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player Destroyed with Param(%p)", this);
}

void Square_Player::Init(SDL_Renderer* renderer)
{
	rect.x = 70;
	rect.y = 70;
	rect.w = 100;
	rect.h = 100;

	R = 255;
	G = 255;
	B = 0;

	PlayerSpeed = 5;
	WalkSpeed = 5;
	RunSpeed = (5 * 2);

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/spritesheet.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Player::Init(SDL_Renderer* renderer, const char* aSpriteLocation,
	int xPosition, int yPosition, 
	int squareWidth, int squareHeight, 
	int colourR, int colourG, int colourB, 
	int Speed)
{
	rect.x = xPosition;
	rect.y = yPosition;
	rect.w = squareWidth;
	rect.h = squareHeight;

	R = colourR;
	G = colourG;
	B = colourB;

	PlayerSpeed = Speed;
	WalkSpeed = Speed;
	RunSpeed = (Speed * 2);

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		aSpriteLocation, // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Player::Input
(int whichKey)
{
	switch (whichKey)
	{
		sprite.isAnimated = true;
		case 'q': // start running
		{
			isRunning = !isRunning;
			if (isRunning)
			{
				sprite.isAnimated = true;
				sprite.spritesPerSecond = 4;
				PlayerSpeed = RunSpeed;
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player now running (%p)", this);
			}
			else
			{
				sprite.isAnimated = true;
				sprite.spritesPerSecond = 2;
				PlayerSpeed = WalkSpeed;
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player now walking (%p)", this);
			}
			break;
		}
		case 'f': // start running
		{
			autoMove = !autoMove;
			if (autoMove)
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player now automoving (%p)", this);
			}
			else
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player no longer automoving (%p)", this);
			}
			break;
		}
		case 'w': // move up
		{
			sprite.isAnimated = true;
			movingUp = true;
			movingDown = false;
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player moving up (%p)", this);
			break;
		}
		case 'a': // move left
		{
			sprite.isAnimated = true;
			movingLeft = true;
			movingRight = false;
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player moving down (%p)", this);
			break;
		}
		case 's': // move down
		{
			sprite.isAnimated = true;
			movingDown = true;
			movingUp = false;
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player moving left (%p)", this);
			break;
		}
		case 'd': // move right
		{
			sprite.isAnimated = true;
			movingRight = true;
			movingLeft = false;
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player moving right (%p)", this);
			break;
		}
		default:
			if (!autoMove)
			{ // if auto moving, player will keep moving when nothing is pressed, otherwise stop walking
				//sprite.isAnimated = false;
				movingUp = false;
				movingLeft = false;
				movingDown = false;
				movingRight = false;
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player at a standstill (%p)", this);
			}
			else
			{}
			break;
	}
}

void Square_Player::Update()
{
	if (movingUp)
	{
		rect.y = (rect.y - PlayerSpeed);
	}
	if (movingLeft)
	{
		rect.x = (rect.x - PlayerSpeed);
	}
	if (movingDown)
	{
		rect.y = (rect.y + PlayerSpeed);
	}
	if (movingRight)
	{
		rect.x = (rect.x + PlayerSpeed);
	}
	else
	{
		rect.x = rect.x;
		rect.y = rect.y;
	}

	// check if player is going out of bounds
	if (rect.x < 50)
	{
		rect.x = 50;
	}
	if (rect.x > 650)
	{
		rect.x = 650;
	}
	if (rect.y < 0)
	{
		rect.y = 0;
	}
	if (rect.y > 450)
	{
		rect.y = 450;
	}

	sprite.Update(rect.x, rect.y);
}

// ENEMY SQUARE

Square_Enemy::Square_Enemy()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy Constructed with Param(%p)", this);
}

Square_Enemy::~Square_Enemy()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy Destroyed with Param(%p)", this);
}

void Square_Enemy::Init(SDL_Renderer* renderer)
{
	rect.x = 70;
	rect.y = 70;
	rect.w = 100;
	rect.h = 100;

	R = 255;
	G = 0;
	B = 0;

	EnemySpeed = 3;

	movementType = 1;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/spritesheetANGRY.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Enemy::Init(SDL_Renderer* renderer, int xPosition, int yPosition, int squareWidth, int squareHeight, int colourR, int colourG, int colourB, int Speed, int aRX, int aRY, int aM)
{
	rect.x = xPosition;
	rect.y = yPosition;
	rect.w = squareWidth;
	rect.h = squareHeight;

	R = colourR;
	G = colourG;
	B = colourB;

	EnemySpeed = Speed;

	respawnX = aRX;
	respawnY = aRY;
	
	movementType = aM;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/spritesheetANGRY.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Enemy::Update(SDL_Renderer* renderer)
{
	sprite.Update(rect.x, rect.y);

	counter++;
	if (isDead)
	{
		if (counter > TTD)
		{
			// sprite shows opacity
			isDead = false;
			counter = 0;
			sprite.SetColour(R, G, B, 255);
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy Respawned with Param(%p)", this);
		}
		return;
	}
	else
	{
		if (counter > TTL)
		{
			Death(renderer);
			return;
		}
	}
	switch (movementType)
	{
	case 1: // move down, then up, repeat
		if (movingForward)
		{
			rect.y = (rect.y + EnemySpeed);
			if (rect.y > 452)
			{
				movingForward = false;
			}
		}
		else
		{
			rect.y = (rect.y - EnemySpeed);
			if (rect.y < 0)
			{
				movingForward = true;
			}
		}
		break;
	case 2: // space invader movement
		if (movingForward)
		{
			rect.x = (rect.x + EnemySpeed);
			if (rect.x > 652)
			{
				rect.y = (rect.y + 50);
				movingForward = false;
			}
		}
		else
		{
			rect.x = (rect.x - EnemySpeed);
			if (rect.x < 48)
			{
				rect.y = (rect.y + 50);
				movingForward = true;
			}
		}
		break;
	default:
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy Param(%p) cannot move", this);
		break;
	}
}

void Square_Enemy::Death(SDL_Renderer* renderer)
{
	isDead = true;
	counter = 0;
	sprite.SetColour(R, G, B, 0);
	rect.x = respawnX;
	rect.y = respawnY;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy Expired with Param(%p)", this);
}

// Bullet SQUARE

Square_Bullet::Square_Bullet()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet Constructed with Param(%p)", this);
}

Square_Bullet::~Square_Bullet()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet Destroyed with Param(%p)", this);
}

void Square_Bullet::Init(SDL_Renderer* renderer)
{
	rect.x = 20;
	rect.y = 20;
	rect.w = 5;
	rect.h = 5;

	R = 255;
	G = 0;
	B = 0;

	BulletSpeed = 7;

	velocity.X = 0;
	velocity.Y = 0;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/bullet.png", // where sprite is located
		1, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		false, // is this sprite animated?
		1, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Bullet::Init(SDL_Renderer* renderer, 
	int xPosition, int yPosition, 
	int squareWidth, int squareHeight, 
	int colourR, int colourG, int colourB, 
	int Speed)
{
	rect.x = xPosition;
	rect.y = yPosition;
	rect.w = squareWidth;
	rect.h = squareHeight;

	R = colourR;
	G = colourG;
	B = colourB;

	BulletSpeed = Speed;

	sprite.Init(
		renderer, // output renderer
		rect.x, rect.y,	// XY position where sprite will appear
		rect.w, rect.h,		// XY size of sprite
		"content/sprites/bullet.png", // where sprite is located
		1, // how many sprites is on each row
		1, // how many sprites is on each column
		true, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		false, // is this sprite animated?
		1, // if animated, how many sprites does it go through per second?
		R, G, B, 255);

	sprite.SetColour(R, G, B, 255);
}

void Square_Bullet::Update(SDL_Renderer* renderer)
{
	rect.x = rect.x - (velocity.X / 17);
	rect.y = rect.y - (velocity.Y / 17);

	sprite.Render(renderer);
}