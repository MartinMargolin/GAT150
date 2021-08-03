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

	//USE THIS AT OWN DISCRETION, IS FUN BUT BE CAREFUL

	/*
	SDL_Window* windows[450];

	for (int i = 0; i < 50; i++)
	{
		
			windows[i] = SDL_CreateWindow("Gat150 | :)", 100 + (i * 10), 100 + (i * 10), 800, 600, SDL_WINDOW_SHOWN);
		
			windows[i + 25] = SDL_CreateWindow("Gat150 | :)", 200 + (i * 10), 100 + (i * 10), 800, 600, SDL_WINDOW_SHOWN);
			windows[i + 50] = SDL_CreateWindow("Gat150 | :)", 300 + (i * 10), 100 + (i * 10), 800, 600, SDL_WINDOW_SHOWN);
			windows[i + 75] = SDL_CreateWindow("Gat150 | :)", 400 + (i * 10), 100 + (i * 10), 800, 600, SDL_WINDOW_SHOWN);
			windows[i + 100] = SDL_CreateWindow("Gat150 | :)", 500 + (i * 10), 100 + (i * 10), 800, 600, SDL_WINDOW_SHOWN);
		
	}

	if (windows == nullptr)
	{
		std::cout << "SDL_CreateWindowError: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;

	}
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