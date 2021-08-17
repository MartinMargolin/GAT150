#pragma once
#include "Component.h"

namespace smile
{
	class Renderer;

	class GraphicsComponent : public Component
	{
	public:
			virtual void Draw(Renderer* renderer) = 0;
	};
}