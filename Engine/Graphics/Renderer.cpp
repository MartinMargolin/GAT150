#include "Renderer.h"
#include <SDL_image.h>
#include <iostream>
#include "Math/MathUtils.h"

namespace smile {
	void Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{

			std::cout << "SDL_Init Error." << SDL_GetError() << std::endl;

		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		IMG_Quit();
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void Renderer::Update(float dt)
	{
	}

	void Renderer::Create(const std::string& name, int width, int height)
	{

		 window = SDL_CreateWindow(name.c_str(), 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		// SDL_WINDOWPOS_CENTERED on both X and Y Places Screen Centered

		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindowError: " << SDL_GetError() << std::endl;
			SDL_Quit();

		}

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

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::BeginFrame()
	{
		SDL_RenderClear(renderer);
	}

	void Renderer::EndFrame()
	{

		SDL_RenderPresent(renderer);
	}

	void Renderer::Draw(std::shared_ptr<smile::Texture> texture, const Vector2& position, float angle, const Vector2& scale)
	{
		Vector2 size = texture->GetSize();

		size = size * scale;

		Vector2 newPosition = position - (size * 0.5f);

		SDL_Rect rect;

		rect.x = static_cast<int>(newPosition.x);
		rect.y = static_cast<int>(newPosition.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &rect, smile::RadToDeg(angle), nullptr, SDL_FLIP_NONE);
	}
	void Renderer::Draw(std::shared_ptr<smile::Texture> texture, const Transform& transform)
	{
		Vector2 size = texture->GetSize();

		size = size * transform.scale;

		Vector2 newPosition = transform.position - (size * 0.5f);

		SDL_Rect rect;

		rect.x = static_cast<int>(newPosition.x);
		rect.y = static_cast<int>(newPosition.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &rect, smile::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}
}