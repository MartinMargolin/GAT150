#include "Font.h"
#include <cassert>
namespace smile
{
	Font::~Font()
	{
		if (font != nullptr)
		{
			TTF_CloseFont(font);
		}
	}

	bool Font::Load(const std::string& name, void* data)
	{

		assert(data);

		font = TTF_OpenFont(name.c_str(), *(static_cast<int*>(data)));
		if (font == nullptr)
		{
			std::cout << "TTF_OpenFront Error:" << TTF_GetError() << std::endl;
			return false;
		}

		return true;
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const smile::Color& color)
	{
		
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color(color));
			if (surface == nullptr)
			{
				std::cout << "TTF_RenderText_Solid Error:" << SDL_GetError() << std::endl;
			}
			return surface;
	}
}