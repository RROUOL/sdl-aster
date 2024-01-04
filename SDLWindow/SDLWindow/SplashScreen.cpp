#include "SZ_GameWorld.h"

// SPLASH SCREEN

SplashScreen::~SplashScreen()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Splash Screen Scene Destroyed with Param(%p)", this);
}

void SplashScreen::run(SDL_Window* window, SDL_Renderer* renderer)
{
	//SDL_Window* window = SDL_CreateWindow("SPLASH SCREEN - Raine Reynolds-Osborne 25151585", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_RESIZABLE);
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetWindowTitle(window, "SPLASH SCREEN - Raine Reynolds-Osborne 25151585");

	SDL_RenderSetLogicalSize(renderer, 800, 600);

	// INIT

	// Initialise SDL2_Image

	IMG_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);

	// objects here

	std::cout << pR << std::endl;
	std::cout << pG << std::endl;
	std::cout << pB << std::endl;
	std::cout << pO << std::endl;


	// fullscreen toggle
	bool isFullScreen = false;

	asterLogo.Init(
		renderer,
		250, 100,
		300, 100,
		"content/sprites/AsterLogo.png",
		1,
		1,
		false,
		false,
		false,
		1,
		pR, pG, pB, pO);

	asterLogo.SetColour(pR, pG, pB, pO);

	switch (pE)
	{
	case 'N':
		astie.Init(
		renderer, // output renderer
		368, 400,	// XY position where sprite will appear
		96, 96,		// XY size of sprite
		"content/sprites/spritesheet.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		pR, pG, pB, pO);
		break;
	case 'H':
		astie.Init(
		renderer, // output renderer
		368, 400,	// XY position where sprite will appear
		96, 96,		// XY size of sprite
		"content/sprites/spritesheetHAPPY.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		pR, pG, pB, pO);
		break;
	case 'A':
		astie.Init(
		renderer, // output renderer
		368, 400,	// XY position where sprite will appear
		96, 96,		// XY size of sprite
		"content/sprites/spritesheetANGRY.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		pR, pG, pB, pO);
		break;
	default:
		astie.Init(
		renderer, // output renderer
		368, 400,	// XY position where sprite will appear
		96, 96,		// XY size of sprite
		"content/sprites/spritesheet.png", // where sprite is located
		4, // how many sprites is on each row
		1, // how many sprites is on each column
		false, // can the sprite flip its X axis?
		false, // can the sprite flip its Y axis?
		true, // is this sprite animated?
		4, // if animated, how many sprites does it go through per second?
		pR, pG, pB, pO);
		break;
	}
	 
	astie.SetColour(pR, pG, pB, pO);

	controls.Init(
		renderer,
		0, 0,
		800, 600,
		"content/sprites/Controls.png",
		1,
		1,
		false,
		false,
		false,
		1,
		0, 255, 255, 255);

	playerCursor.Init(renderer, cursorR, cursorG, cursorB, cursorB);

	cursorTrail_1.Init(renderer, 12, 0, 8, -8, -8, 8, -8, cursorR, cursorG, cursorB, 204);
	cursorTrail_2.Init(renderer, 12, 0, 6, -6, -6, 6, -6, cursorR, cursorG, cursorB, 153);
	cursorTrail_3.Init(renderer, 12, 0, 4, -4, -4, 4, -4, cursorR, cursorG, cursorB, 102);
	cursorTrail_4.Init(renderer, 12, 0, 2, -2, -2, 2, -2, cursorR, cursorG, cursorB, 51);

	while (!done)
	{
		std::cout << "\nnew loop\n" << std::endl;
		frameCounter++;
		printf("FRAME NUMBER: %i\n\n)", frameCounter);

		// RENDER
		printf("RENDER TICKS: ", aTimer.getTicks());

		// render objects
		SDL_SetRenderDrawColor(renderer, bgR, bgG, bgB, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		

		// render objects
		/*
		std::cout << "SplashScreen sprite called" << std::endl;

		SDL_RenderCopy(renderer, currentImage, &playerRect, &playerPosition);
		*/
		// sprites
		asterLogo.Render(renderer);
		astie.Render(renderer);
		controls.Render(renderer);

		cursorTrail_1.Render(renderer);
		cursorTrail_2.Render(renderer);
		cursorTrail_3.Render(renderer);
		cursorTrail_4.Render(renderer);
		playerCursor.Render(renderer);

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

			if (_event.type == SDL_KEYDOWN)
			{
				keystate = SDL_GetKeyboardState(NULL);
				if (keystate[SDL_SCANCODE_E]) done = true;
				if (keystate[SDL_SCANCODE_SPACE]) isFullScreen = toggleFullScreen(window, renderer, isFullScreen);
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

		//UPDATE
		printf("UPDATE TICKS: ", aTimer.getTicks());

		asterLogo.Update();
		astie.Update();
		controls.Update();

		// background colour changes over time
		if (isIncreasing)
		{
			if ((bgR + 1) < 128)
			{
				bgR++;
			}
			else
			{
				isIncreasing = false;
			}
		}
		else
		{
			if ((bgR - 1) > 0)
			{
				bgR--;
			}
			else
			{
				isIncreasing = true;
			}
		}
		if (isIncreasing)
		{
			if ((bgG + 1) < 128)
			{
				bgG++;
			}
			else
			{
				isIncreasing = false;
			}
		}
		else
		{
			if ((bgG - 1) > 0)
			{
				bgG--;
			}
			else
			{
				isIncreasing = true;
			}
		}
		if (isIncreasing)
		{
			if ((bgB + 1) < 128)
			{
				bgB++;
			}
			else
			{
				isIncreasing = false;
			}
		}
		else
		{
			if ((bgB - 1) > 0)
			{
				bgB--;
			}
			else
			{
				isIncreasing = true;
			}
		}


		cursorTrail_4.updatePos(cursorTrail_3.currentPositionX, cursorTrail_3.currentPositionY);
		cursorTrail_3.updatePos(cursorTrail_2.currentPositionX, cursorTrail_2.currentPositionY);
		cursorTrail_2.updatePos(cursorTrail_1.currentPositionX, cursorTrail_1.currentPositionY);
		cursorTrail_1.updatePos(playerCursor.currentPositionX, playerCursor.currentPositionY);

		// WAIT FOR TICKS
		printf("FINAL TICKS: ", aTimer.getTicks());
		if (aTimer.getTicks() < 17)
		{
			SDL_Delay(17 - aTimer.getTicks());
		}

	}

	// destroy all objects on shutdown

	// sprites

	asterLogo.~Sprite();
	astie.~Sprite();
	controls.~Sprite();

	// cursors
	playerCursor.~RO_Cursor();
	cursorTrail_1.~RO_Cursor();
	cursorTrail_2.~RO_Cursor();
	cursorTrail_3.~RO_Cursor();
	cursorTrail_4.~RO_Cursor();

	// destroy images
	IMG_Quit();

	printf("shutting down");
}