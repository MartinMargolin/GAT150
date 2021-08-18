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

	std::unique_ptr<smile::Actor> actor = std::make_unique<smile::Actor>(smile::Transform{ {400, 300}});
	{

	std::unique_ptr<smile::SpriteComponent> component = std::make_unique<smile::SpriteComponent>();
	component->texture = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("treeSnake.png", engine->Get<smile::Renderer>());
	actor->AddComponent(std::move(component));

	}

	/*{

		std::unique_ptr<smile::PhysicsComponent> component = std::make_unique<smile::PhysicsComponent>();
		component->ApplyForce(smile::Vector2::right * 200);
		actor->AddComponent(std::move(component));


	}*/

	scene->AddActor(std::move(actor));

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