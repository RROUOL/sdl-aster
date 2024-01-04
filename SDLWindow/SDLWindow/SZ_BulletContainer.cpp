#include "SZ_BulletContainer.h"

SZ_BulletContainer::SZ_BulletContainer()
{

}
SZ_BulletContainer::~SZ_BulletContainer()
{
	for (size_t i = 0; i < aListofBullets.size(); i++)
	{
		aListofBullets[i]->~Square_Bullet();
	}
}

void SZ_BulletContainer::Init(SDL_Renderer* renderer, int eY, int eX, int eNum, int TTL)
{
	X = eX; Y = eY;
	Num = eNum;
	aRect.x = X; aRect.y = Y;
	aRect.w = 20; aRect.h = 20;
	for (int i = 0; i < Num; i++)
	{
		int PosX = X;
		int PosY = Y;
		Add(renderer, PosX, PosY);
	}
	this->TTL = TTL;
}

void SZ_BulletContainer::Add(SDL_Renderer* renderer, int X, int Y)
{
	Square_Bullet* aBullet = new Square_Bullet();
	aBullet->sprite.SetColour(255, 128, 0, 255);
	aBullet->velocity.X = 0;
	aBullet->velocity.Y = 0;
	aBullet->Init(renderer, X, Y, 20, 20, 255, 0, 0, 7);
	this->aListofBullets.push_back(aBullet);
}

void SZ_BulletContainer::Input(SDL_Renderer* renderer, int playerX, int playerY, int cursorX, int cursorY)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet being fired by Param(%p)", this);
	for (size_t i = 0; i < aListofBullets.size(); i++)
	{
		if (aListofBullets[i]->velocity.Y == 0)
		{
			aListofBullets[i]->sprite.SetColour(aListofBullets[i]->R, aListofBullets[i]->G, aListofBullets[i]->B, 255);
			

			aListofBullets[i]->velocity.X = (playerX - cursorX);
			aListofBullets[i]->velocity.Y = (playerY - cursorY);

			aListofBullets[i]->rect.x = playerX + 32;
			aListofBullets[i]->rect.y = playerY + 32;

			//X = aListofBullets[i]->rect.x;
			//Y = aListofBullets[i]->rect.y;
		}
		else
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet Container is out of bullets! (%p)", this);
		}
	}
}

void SZ_BulletContainer::Render(SDL_Renderer* aRenderer, bool squareDRAWN)
{
	// render controller for debugging
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(aRenderer, &aRect);
	for (auto& element : aListofBullets)
	{
		if (element->velocity.Y != 0)
		{
			element->sprite.Update();
			element->Render(aRenderer, squareDRAWN);
		}
	}
}

void SZ_BulletContainer::Update(SDL_Renderer* renderer)
{
	for (auto& element : aListofBullets)
	{
		element->Update(renderer);
		if (element->velocity.Y != 0)
		{
			element->LifeCounter++;
		}
		else
		{
			element->x = X;
			element->y = Y;
		}
		if (element->LifeCounter > TTL)
		{
			element->LifeCounter = 0;
			element->x = X;
			element->y = Y;
			element->velocity.Y = 0;
		}
	}
	aRect.x = X;
	aRect.y = Y;
}


vector<Square_Bullet*> aListofBullets;

void SZ_BulletContainer::Shoot()
{
	int i = 0;
	bool NotFound = true;
	while ((i < aListofBullets.size()) && (NotFound))
	{
		if (aListofBullets[i]->velocity.Y == 0)
		{
			aListofBullets[i]->x = X;
			aListofBullets[i]->y = Y;
			aListofBullets[i]->LifeCounter = 0;
			aListofBullets[i]->velocity.Y = 10;
			NotFound = false;

		}
		i++;
	}
}
