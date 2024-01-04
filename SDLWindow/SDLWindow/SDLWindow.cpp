// SDLWindow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "SDL.h"

#include "SZ_GameWorld.h"
#include "SZ_Timer.h"
#include "SZ_Cursor.h"
#include "SZ_Square.h"
#include "SZ_GameContainerSquare.h"
#include "SZ_BulletContainer.h"

// window & renderer
SDL_Window* window;
SDL_Renderer* renderer;

// scenes
SplashScreen splashScreen;
GameScreen mainGameWorld;
EndScreen endScreen;

// fullscreen toggle
bool isFullScreen = false;

// score
int score = 0;

//std::vector<SZ_Square*> aSquareList;


std::vector<std::string> CompileSpecs()
{
	std::vector<std::string> empty; // this is returned if the file is failed to be read

	fstream readFile;
	readFile.open("content/other/specs.txt", ios::in);
	if (readFile.is_open())
	{

		std::string line;
		std::string lineTotal;
		
		std::vector<std::string> result;

		stringstream specs(line);

		for (int i = 0; i < 12; i++)
		{
			string substr;
			getline(readFile, line, ',');
			result.push_back(line);
			std::cout << "result full array: " << std::endl;
			for (int i = 0; i < result.size(); i++)
			{
				
				std::cout << result[i] << std::endl;
			}
			
			std::cout << "size of result array: " << std::endl;
			std::cout << result.size() << std::endl;
		}
		if (result.size() != 12)
		{
			printf("TXT_Load: SPECS.TXT HAS INCORRECT PARAMS (%i)\n", result.size());
			return empty;
		}
		char playerE = result[0].at(0);
		switch (playerE)
		{
		case 'N':
			printf("TXT_Load: Normal spritesheet chosen.");
			break;
		case 'H':
			printf("TXT_Load: Happy spritesheet chosen.");
			break;
		case 'A':
			printf("TXT_Load: Angry spritesheet chosen.");
			break;
		default:
			printf("TXT_Load: PARAM 1 IS INCORRECT\n");
			return empty;
			break;
		}

		for (int i = 1; i < result.size(); i++)
		{
			if ((stoi(result[i]) < 0) || (result[i].find_first_not_of("0123456789") != std::string::npos))
			{
				printf("TXT_Load: PARAM %i IS INCORRECT\n", i);
				std::cout << result[i] << std::endl;
				return empty;
			}
			if ((stoi(result[i]) > 255) || (result[i].find_first_not_of("0123456789") != std::string::npos))
			{
				printf("TXT_Load: PARAM %i IS INCORRECT\n", i);
				return empty;
			}
		}

		printf("TXT_Load: PARAMS CHECK CLEAR\n");
		return result;


	}
	else
	{
		printf("TXT_Load: SPECS.TXT NOT FOUND\n");
		return empty;
	}
}


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;

	window = SDL_CreateWindow("ASTER - Raine Reynolds-Osborne 25151585", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// create window and renderer which will be used by scenes

	std::vector<std::string> specs = CompileSpecs();

	if (specs.size() == 12)
	{
		char playerE = specs[0].at(0);

		splashScreen.init(
			playerE, stoi(specs[1]), stoi(specs[2]), stoi(specs[3]), stoi(specs[4]), // player specs
			stoi(specs[5]), stoi(specs[6]), stoi(specs[7]), stoi(specs[8]), // cursor specs
				stoi(specs[9]), stoi(specs[10]), stoi(specs[11])); // background specs
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "SCENE 1 NOW PLAYING");
	splashScreen.run(window, renderer);
	splashScreen.~SplashScreen();

	specs = CompileSpecs();

	if (specs.size() == 12)
	{
		char playerE = specs[0].at(0);

		mainGameWorld.init(
			playerE, stoi(specs[1]), stoi(specs[2]), stoi(specs[3]), stoi(specs[4]), // player specs
			stoi(specs[5]), stoi(specs[6]), stoi(specs[7]), stoi(specs[8]), // cursor specs
			stoi(specs[9]), stoi(specs[10]), stoi(specs[11])); // background specs
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "SCENE 2 NOW PLAYING");
	score = mainGameWorld.run(window, renderer);
	mainGameWorld.~GameScreen();

	specs = CompileSpecs();

	if (specs.size() == 12)
	{
		char playerE = specs[0].at(0);

		endScreen.init(
			playerE, stoi(specs[1]), stoi(specs[2]), stoi(specs[3]), stoi(specs[4]), // player specs
			stoi(specs[5]), stoi(specs[6]), stoi(specs[7]), stoi(specs[8]), // cursor specs
			stoi(specs[9]), stoi(specs[10]), stoi(specs[11])); // background specs
	}
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "SCENE 3 NOW PLAYING");
	endScreen.run(window, renderer, score);
	endScreen.~EndScreen();


	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "SCORE: %i", score);
	SDL_Quit();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
