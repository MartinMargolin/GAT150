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


	engine->Get<smile::AudioSystem>()->AddAudio("edamame", "audio/edamame.mp3");
	engine->Get<smile::AudioSystem>()->PlayAudio("edamame", true);

	engine->Get<smile::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
	engine->Get<smile::EventSystem>()->Subscribe("remove_score", std::bind(&Game::OnRemoveScore, this, std::placeholders::_1));



	/*
	


	for (int i = 0; i < 10; i++)
	{

		auto actor = smile::ObjectFactory::Instance().Create<smile::Actor>("Coin");
		actor->transform.position = smile::Vector2{ smile::RandomRange(0,800), smile::RandomRange(100 ,300) };
		scene->AddActor(std::move(actor));

	}
	*/
	

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();


	quit = (engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == smile::InputSystem::eKeyState::PRESSED);

	switch (state)
	{
	case Game::eState::Launch:
		Launch();
		break;
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	auto scoreActor = scene->FindActor("Score");
	if (scoreActor)	scoreActor->GetComponent<smile::TextComponent>()->SetText(std::to_string(score));
	scene->Update(engine->time.deltaTime);

}

void Game::Draw()
{

	engine->Get<smile::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<smile::Renderer>());
	scene->Draw(engine->Get<smile::Renderer>());

	engine->Get<smile::Renderer>()->EndFrame();


}

void Game::Launch()
{
	if (!loaded)
	{
		loaded = true;

		rapidjson::Document document;
		bool success = smile::json::Load("launch.txt", document);
		assert(success);
		scene->Read(document);
		scene->Update(0);
	}


	stateTimer += engine->time.deltaTime;



	if (stateTimer >= 2.6)
	{
		auto title = scene->FindActor("Smile");
		title->active = true;

	}

	if (stateTimer >= 3.1)
	{
		auto title = scene->FindActor("Studios");
		title->active = true;
	}
	
	if (stateTimer >= 4)
	{
		auto title = scene->FindActor("MoneyGrab");
		title->active = true;
	}

	if (stateTimer >= 5.5)
	{
		state = eState::Reset;
	}

}

void Game::Reset()
{
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = smile::json::Load("title.txt", document);
	assert(success);
	scene->Read(document);

	state = eState::Title;
}


void Game::Title()
{
	if (engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == smile::InputSystem::eKeyState::PRESSED)
	{
		auto title = scene->FindActor("Space");

		title->active = false;

		title = scene->FindActor("MoneyGrab");

		title->active = false;

		state = eState::StartGame;
	}
}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = smile::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);
	
	smile::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = smile::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1)
	{
		auto player = smile::ObjectFactory::Instance().Create<smile::Actor>("Player");
		player->transform.position = smile::Vector2{ 400, 350 };
		scene->AddActor(std::move(player));

		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = smile::RandomRange(1, 1.5);
		auto coin = smile::ObjectFactory::Instance().Create<smile::Actor>("Coin");
		coin->transform.position = smile::Vector2{ smile::RandomRange(100, 700), smile::RandomRange(100, 400) };
		scene->AddActor(std::move(coin));
	}
}

void Game::PlayerDead()
{

}

void Game::GameOver()
{

}

void Game::OnAddScore(const smile::Event& event)
{
	score +=std::get<int>(event.data);
}


void Game::OnRemoveScore(const smile::Event& event)
{
	score -= std::get<int>(event.data);
}
