#pragma once
#include "Component/Component.h"
#include "Math//Vector2.h"

namespace smile
{
	class PhysicsComponent : public Component
	{
	public:
		void Update() override;
		void ApplyForce(const Vector2& force) { accelleration += force; }

		public:
		Vector2 velocity;
		Vector2 accelleration;
	};
}