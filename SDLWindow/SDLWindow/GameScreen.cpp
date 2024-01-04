#include "SZ_GameWorld.h"

// Game SCREEN

GameScreen::~GameScreen()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Screen Scene Destroyed with Param(%p)", this);
}

int GameScreen::run(SDL_Window* window, SDL_Renderer* renderer)
{
	int score = 0;


	SDL_SetWindowTitle(window, "ASTER - Raine Reynolds-Osborne 25151585");

	// game scales at 800x600 resolution
	SDL_RenderSetLogicalSize(renderer, 800, 600);

	// keeps track of what buttons are pressed
	bool spacePressed = false;
	bool qPressed = false;
	bool fPressed = false;
	bool ePressed = false;
	bool iPressed = false;

	// renders rect when '1' is pressed
	bool squareDRAW = false;

	// Initialise SDL2_Image

	IMG_Init(SDL_INIT_EVERYTHING);


	//Load in png
	SDL_Surface* surface = IMG_Load("content/sprite.png");
	//Convert to a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,
		surface);
	//Free up the surface data from RAM
	SDL_FreeSurface(surface);




	// INIT

	// cursors
	playerCursor.Init(renderer, cursorR, cursorG, cursorB, cursorB);

	cursorTrail_1.Init(renderer, 12, 0, 8, -8, -8, 8, -8, cursorR, cursorG, cursorB, 204);
	cursorTrail_2.Init(renderer, 12, 0, 6, -6, -6, 6, -6, cursorR, cursorG, cursorB, 153);
	cursorTrail_3.Init(renderer, 12, 0, 4, -4, -4, 4, -4, cursorR, cursorG, cursorB, 102);
	cursorTrail_4.Init(renderer, 12, 0, 2, -2, -2, 2, -2, cursorR, cursorG, cursorB, 51);


	// squares
		// player
	switch (pE)
	{
	case 'N':
		playerSquare.Init(renderer, "content/sprites/spritesheet.png",
			400, 300,
			100, 100,
			pR, pG, pB, 3);
		break;
	case 'H':
		playerSquare.Init(renderer, "content/sprites/spritesheetHAPPY.png",
			400, 300,
			100, 100,
			pR, pG, pB, 3);
		break;
	case 'A':
		playerSquare.Init(renderer, "content/sprites/spritesheetANGRY.png",
			400, 300,
			100, 100,
			pR, pG, pB, 3);
		break;
	default:
		playerSquare.Init(renderer, "content/sprites/spritesheet.png", 
		400, 300, 
		100, 100, 
		pR, pG, pB, 3);
		break;
	}

		// walls
	leftWallContainerSquare.Init(renderer, "content/sprites/Block.png", 0, 0, 0.0f, 1.0f, 12);
	rightWallContainerSquare.Init(renderer, "content/sprites/Block.png", 750, 0, 0.0f, 1.0f, 12);
	downWallContainerSquare.Init(renderer, "content/sprites/Block.png", 50, 550, 1.0f, 0.0f, 14);

		// enemy
	enemy1.Init(renderer, 70, 0, 64, 64, 255, 0, 0, 3, 70, 0, 1);
	enemy2.Init(renderer, 140, 0, 64, 64, 255, 0, 0, 3, 140, 0, 2);
	enemy3.Init(renderer, 210, 0, 64, 64, 255, 0, 0, 3, 210, 0, 1);

		// bullet container
	aBulletContainer.Init(renderer, 0, 0, 1, 60);

	// fullscreen toggle
	bool isFullScreen = false;

	// START LOOP
	while (!done)
	{
		std::cout << "new loop\n" << std::endl;
		frameCounter++;
		printf("Frame: %i)\n", frameCounter);

		// SCORE KEEPING

		if (score < 10000 && frameCounter > 3600)
		{
			done = true; // game ends at 60s if score is lower than 10k
		}
		else if (frameCounter > 4500)
		{
			done = true; // game ends at 75s if score is greater than 10k
		}

		// RENDER
		printf("RENDER TICKS: ", aTimer.getTicks());

		SDL_SetRenderDrawColor(renderer, bgR, bgG, bgB, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// render objects
		playerSquare.Render(renderer, squareDRAW);
		leftWallContainerSquare.Render(renderer, squareDRAW);
		rightWallContainerSquare.Render(renderer, squareDRAW);
		downWallContainerSquare.Render(renderer, squareDRAW);

		enemy1.Render(renderer, squareDRAW);
		enemy2.Render(renderer, squareDRAW);
		enemy3.Render(renderer, squareDRAW);

		cursorTrail_1.Render(renderer);
		cursorTrail_2.Render(renderer);
		cursorTrail_3.Render(renderer);
		cursorTrail_4.Render(renderer);
		playerCursor.Render(renderer);

		aBulletContainer.Render(renderer, squareDRAW);

		

		// everything above is rendered

		SDL_RenderPresent(renderer);

		// RESET TICKS

		aTimer.resetTicksTimer();

		// INPUT
		printf("INPUT TICKS: ", aTimer.getTicks());

		SDL_Event _event;

		while (SDL_PollEvent(&_event))
		{
			if (_event.type == SDL_QUIT) done = true;

			keystate = SDL_GetKeyboardState(NULL);
			std::cout << "keystate: " << keystate << std::endl;
			if (keystate[SDL_SCANCODE_ESCAPE]) done = true;
			else if (keystate[SDL_SCANCODE_I])
			{
				if (!iPressed)
				{
					SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "SquareDRAW toggled");
					if (squareDRAW)
					{
						squareDRAW = false;
					}
					else
					{
						squareDRAW = true;
					}
					iPressed = true;
				}
				else
				{
					iPressed = false;
				}
			}
			else if (keystate[SDL_SCANCODE_SPACE])
			{
				if (!spacePressed)
				{
					isFullScreen = toggleFullScreen(window, renderer, isFullScreen);
					spacePressed = true;
				}
				else
				{
					spacePressed = false;
				}
			}
			else if (keystate[SDL_SCANCODE_Q])
			{
				if (!qPressed)
				{
					playerSquare.Input('q'); qPressed = true;
				}
				else
				{
					qPressed = false;
				}
			}
			else if (keystate[SDL_SCANCODE_F])
			{
				if (!fPressed)
				{
				playerSquare.Input('f'); fPressed = true;
				}
				else
				{
					fPressed = false;
				}
			}
			else if (keystate[SDL_SCANCODE_E])
			{
				if (!ePressed)
				{
					aBulletContainer.Input(renderer, playerSquare.rect.x, playerSquare.rect.y, playerCursor.currentPositionX, playerCursor.currentPositionY); ePressed = true;
				}
				else
				{
					ePressed = false;
				}
			}
			else if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) playerSquare.Input('w');
			else if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) playerSquare.Input('a');
			else if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) playerSquare.Input('s');
			else if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) playerSquare.Input('d');
			else
			{
				playerSquare.Input(' ');
			}

			if (_event.type == SDL_MOUSEMOTION)
			{
				mousePosition = SDL_GetMouseState(&mousePosX, &mousePosY);

				// currentPositiont);
				MouseMoveCounter++;

				if ((mousePosX > 0) && (mousePosY > 0))
				{
					playerCursor.updatePos(mousePosX, mousePosY);
				}
			}

		}

		// UPDATE
		printf("UPDATE TICKS: ", aTimer.getTicks());

		// squares
		playerSquare.Update();
		// cursor
		cursorTrail_4.updatePos(cursorTrail_3.currentPositionX, cursorTrail_3.currentPositionY);
		cursorTrail_3.updatePos(cursorTrail_2.currentPositionX, cursorTrail_2.currentPositionY);
		cursorTrail_2.updatePos(cursorTrail_1.currentPositionX, cursorTrail_1.currentPositionY);
		cursorTrail_1.updatePos(playerCursor.currentPositionX, playerCursor.currentPositionY);

		// square container
		leftWallContainerSquare.Update();
		rightWallContainerSquare.Update();
		downWallContainerSquare.Update();

		// bullet container
		aBulletContainer.Update(renderer);

		// enemies
		enemy1.Update(renderer);
		enemy2.Update(renderer);
		enemy3.Update(renderer);

		// CHECK FOR COLLISIONS

			// Players and Enemies..
		// enemy1
		if (checkCollision(playerSquare.rect, enemy1.rect))
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy 1 killed Player!");
			// play sound effect
			SDL_Delay(1000);
			done = true;

		}
		// enemy2
		if (checkCollision(playerSquare.rect, enemy2.rect))
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy 2 killed Player!");
			// play sound effect
			SDL_Delay(1000);
			done = true;
		}
		// enemy3
		if (checkCollision(playerSquare.rect, enemy3.rect))
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Enemy 3 killed Player!");
			// play sound effect
			SDL_Delay(1000);
			done = true;
		}
			// Bullets and Enemies..
		// enemy1
		for (size_t i = 0; i < aBulletContainer.aListofBullets.size(); i++)
		{
			if (checkCollision(aBulletContainer.aListofBullets[i]->rect, enemy1.rect) && enemy1.isDead == false)
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet (%i) killed Enemy 1!", aBulletContainer.aListofBullets[i]);
				// play sound effect
				enemy1.Death(renderer);
				score = score + 1000;
			}
		}
		// enemy2
		for (size_t i = 0; i < aBulletContainer.aListofBullets.size(); i++)
		{
			if (checkCollision(aBulletContainer.aListofBullets[i]->rect, enemy2.rect) && enemy2.isDead == false)
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet (%i) killed Enemy 2!", aBulletContainer.aListofBullets[i]);
				// play sound effect
				enemy2.Death(renderer);
				score = score + 1000;
			}
		}
		// enemy3
		for (size_t i = 0; i < aBulletContainer.aListofBullets.size(); i++)
		{
			if (checkCollision(aBulletContainer.aListofBullets[i]->rect, enemy3.rect) && enemy3.isDead == false)
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bullet (%i) killed Enemy 3!", aBulletContainer.aListofBullets[i]);
				// play sound effect
				enemy3.Death(renderer);
				score = score + 1000;
			}
		}

		// WAIT FOR TICKS
		printf("FINAL TICKS: ", aTimer.getTicks());
		if (aTimer.getTicks() < 17)
		{
			SDL_Delay(17 - aTimer.getTicks());
		}

	}

	// destroy all objects on shutdown

	// cursors
	playerCursor.~RO_Cursor();
	cursorTrail_1.~RO_Cursor();
	cursorTrail_2.~RO_Cursor();
	cursorTrail_3.~RO_Cursor();
	cursorTrail_4.~RO_Cursor();

	// squares
	playerSquare.~Square_Player();

	leftWallContainerSquare.~SZ_GameContainerSquare();
	rightWallContainerSquare.~SZ_GameContainerSquare();
	downWallContainerSquare.~SZ_GameContainerSquare();
	aBulletContainer.~SZ_BulletContainer();

	// destroy images
	IMG_Quit();

	printf("saving score...");

	return score; // returns score to SDLWindow.cpp, can be used by EndScreen class
}