#include "Game.h"


void Game::Initialize()
{
	engine = std::make_unique<smile::Engine>(); // New Engine
	engine->Startup();
	engine->Get<smile::Renderer>()->Create(":)", 800, 600);

	scene = std::make_unique<smile::Scene>(); // New Scene
	scene->engine = engine.get();


	smile::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	smile::SetFilePath("../Resources");

	std::unique_ptr<smile::Actor> actor1 = std::make_unique<smile::Actor>(smile::Transform{ smile::Vector2{200,300}, 0, 1 });
	{
	
		auto component = smile::ObjectFactory::Instance().Create<smile::SpriteAnimationComponent>("SpriteAnimationComponent");
		component->texture = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("sparkle.png", engine->Get<smile::Renderer>());
		component->fps = 30;
		component->numFramesX = 8;
		component->numFramesY = 8;
		actor1->AddComponent(std::move(component));
	}

	std::unique_ptr<smile::Actor> actor2 = std::make_unique<smile::Actor>(smile::Transform{ smile::Vector2{600,300}, 0, 3 });
	{

		smile::SpriteAnimationComponent* component = actor2->AddComponent<smile::SpriteAnimationComponent>();
		component->texture = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("link.png", engine->Get<smile::Renderer>());
		component->fps = 120;
		component->numFramesX = 12;
		component->numFramesY = 8;

	}

	/*{

		std::unique_ptr<smile::PhysicsComponent> component = std::make_unique<smile::PhysicsComponent>();
		component->ApplyForce(smile::Vector2::right * 200);
		actor->AddComponent(std::move(component));


	}*/

	scene->AddActor(std::move(actor1));
	scene->AddActor(std::move(actor2));




	/*int size = 32;
	std::shared_ptr<smile::Font> titleFont = engine->Get<smile::ResourceSystem>()->Get<smile::Font>("fonts/ALBAS.ttf", &size);

	{
		std::unique_ptr<smile::SpriteComponent> component = std::make_unique<smile::SpriteComponent>();
		component->texture = titleFont;

	}*/

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	scene->Update(engine->time.deltaTime);

	quit = (engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == smile::InputSystem::eKeyState::PRESSED);
}

void Game::Draw()
{

	engine->Get<smile::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<smile::Renderer>());
	scene->Draw(engine->Get<smile::Renderer>());

	engine->Get<smile::Renderer>()->EndFrame();


}