#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"


void Game::Initialize()
{
	engine = std::make_unique<smile::Engine>(); // New Engine
	engine->Startup();
	engine->Get<smile::Renderer>()->Create(":)", 800, 600);


	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

	scene = std::make_unique<smile::Scene>(); // New Scene
	scene->engine = engine.get();


	smile::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	smile::SetFilePath("../Resources");

	rapidjson::Document document;
	bool success = smile::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	for (int i = 0; i < 10; i++)
	{

		auto actor = smile::ObjectFactory::Instance().Create<smile::Actor>("Coin");
		actor->transform.position = smile::Vector2{ smile::RandomRange(0,800), smile::RandomRange(100 ,300) };
		scene->AddActor(std::move(actor));

	}
	

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