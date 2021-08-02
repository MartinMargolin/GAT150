#include <iostream>
#include <SDL.h>

int main(int, char**)
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{

		std::cout << "SDL_Init Error." << SDL_GetError() << std::endl;
		return 1;

	}

	SDL_Window* window = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	
	/*
	SDL_Window* window2 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window3 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window4 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window5 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window6 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window7 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Window* window8 = SDL_CreateWindow("Gat150 | :)", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	*/

	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindowError: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	
	}

	// Wait for keypress to exit
	std::getchar();


	SDL_Quit();

}