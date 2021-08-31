#pragma once
// systems


#define REGISTER_CLASS(class) smile::ObjectFactory::Instance().Register<class>(#class);

// core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Json.h"
#include "Core/Serializable.h"

#include "Physics/PhysicsSystem.h"

// math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"
// graphics
#include "Graphics/ParticleSystem.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/Font.h"

// input
#include "Input/InputSystem.h"


//audio
#include "Audio/AudioSystem.h"


// resource
#include "Resource/ResourceSystem.h"

// objects
#include "Object/Actor.h"
#include "Object/Scene.h"

// compoonent

#include "Component/SpriteComponent.h"
#include "Component/GraphicsComponent.h"
#include "Component/SpriteAnimationComponent.h"
#include "Component/Component.h"
#include "Component/RBPhysicsComponent.h"
#include "Component/PhysicsComponent.h"
#include "Component/AudioComponent.h"
#include "Component/TextComponent.h"

#include "Physics/PhysicsSystem.h"

#include <vector>
#include <memory>
#include <algorithm>
namespace smile
{
	using ObjectFactory = Singleton<Factory<std::string, Object>>;



	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();

		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}
