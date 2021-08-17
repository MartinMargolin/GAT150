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
	
	//EFFECTS

	engine->Get<smile::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("weewoo", "audio/weewoo.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("ping", "audio/ping.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("gameover", "audio/gameover.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("bruh", "audio/bruh.mp3");

	//SOUNDTRACKS

	engine->Get<smile::AudioSystem>()->AddAudio("music", "audio/song.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("september", "audio/september.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("dropTop", "audio/dropTop.wav");
	engine->Get<smile::AudioSystem>()->AddAudio("dont", "audio/dont.mp3");
	engine->Get<smile::AudioSystem>()->AddAudio("cozmo", "audio/cozmo.mp3");

	musicChannel = engine->Get<smile::AudioSystem>()->PlayAudio("cozmo", 0.2f, 1.0f, true);

	
	
	// Smile Face
	smile = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("o.png", engine->Get<smile::Renderer>()); 
	ship = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("ship1.png", engine->Get<smile::Renderer>()); 



		
	// text
	int size = 64;
	std::shared_ptr<smile::Font> titleFont = engine->Get<smile::ResourceSystem>()->Get<smile::Font>("fonts/ALBAS.ttf", &size);
	
	 size = 16;
	std::shared_ptr<smile::Font> startText = engine->Get<smile::ResourceSystem>()->Get<smile::Font>("fonts/ALBAS.ttf", &size);

	// particle
	particleTexture = engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("particle01.png", engine->Get<smile::Renderer>());
	titleText = std::make_shared<smile::Texture>(engine->Get<smile::Renderer>());
	titleStart = std::make_shared<smile::Texture>(engine->Get<smile::Renderer>());
	gameOverText = std::make_shared<smile::Texture>(engine->Get<smile::Renderer>());


	// text



	titleText->Create(titleFont->CreateSurface("SMILE", smile::Color{ 1.0f, 1.0f , 1.0f }));
	engine->Get<smile::ResourceSystem>()->Add("titleText", titleText);

	titleStart->Create(startText->CreateSurface("PRESS SPACE TO START :)", smile::Color{1.0f, 1.0f, 1.0f }));
	engine->Get<smile::ResourceSystem>()->Add("titleStart", titleStart);

	gameOverText->Create(startText->CreateSurface("YOU LOST :)", smile::Color{ 1.0f, 1.0f, 1.0f}));
	engine->Get<smile::ResourceSystem>()->Add("titleStart", gameOverText);



	
	// game 
	engine->Get<smile::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<smile::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{

	float dt = engine->time.deltaTime;
	stateTimer += dt;

	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == smile::InputSystem::eKeyState::PRESSED)
		{
			state = eState::StartGame;
			std::cout << "SMILE: GAME START \n";
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		
	/*	musicChannel.Stop();
		musicChannel = engine->Get<smile::AudioSystem>()->PlayAudio("september", 0.2f, 1.0f, true);*/
		
		scene->AddActor(std::make_unique<Player>(smile::Transform{ smile::Vector2{400, 300}, 0.0f, 0.2f }, ship , 450.0f));
		
		
		for (size_t i = 0; i < 2; i++)
		{
			scene->AddActor(std::make_unique<Enemy>(smile::Transform{ smile::Vector2{smile::RandomRange(0.0f, 800.0f), smile::RandomRange(0.0f, 600.0f)}, smile::RandomRange(0.0f, smile::TwoPi), 0.2f }, engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("enemy1.png", engine->Get<smile::Renderer>()) , 100.0f));
		}
		
		
		state = eState::Game;
	}
		break;
	case Game::eState::Game:
		spawnTimer -= dt;
		if (spawnTimer <= 0)
		{
			spawnTimer = smile::RandomRange(1.0f, 3.0f);
			scene->AddActor(std::make_unique<Enemy>(smile::Transform{ smile::Vector2{smile::RandomRange(0.0f, 800.0f), smile::RandomRange(0.0f, 600.0f)}, smile::RandomRange(0.0f, smile::TwoPi), 0.2f }, engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("enemy1.png", engine->Get<smile::Renderer>()), 100.0f));
		}

		break;
	case Game::eState::PlayerDead:
		if (stateTimer >= 2)
		{
			scene->RemoveAllActors();
			state = eState::StartLevel;
		}
		break;


	case Game::eState::GameOver:
		


		if (stateTimer >= 2)
		{
			engine->Get<smile::AudioSystem>()->PlayAudio("gameover", 0.5f, 1.0f, false);
			scene->RemoveAllActors();
			state = eState::Title;
		}
		break;
	default:
		break;
	}

	engine->Update();
	scene->Update(engine->time.deltaTime);

	quit = (engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == smile::InputSystem::eKeyState::PRESSED);

	//if (engine->Get<smile::InputSystem>()->GetButtonState((int)smile::InputSystem::eMouseButton::LEFT) == smile::InputSystem::eKeyState::PRESSED)
	//{
	//	smile::Vector2 position = engine->Get<smile::InputSystem>()->GetMousePosition();
	//	engine->Get<smile::ParticleSystem>()->Create({ position.x, position.y }, 10, 2, particleTexture, 25);
	//	std::cout << position.x << " | " << position.y << std::endl;
	//	engine->Get<smile::AudioSystem>()->PlayAudio("bruh", 1, 1.0f);
	//	//musicChannel.SetPitch(smile::RandomRange(1, 5));
	//}
}

void Game::Draw()
{
	smile::Transform transform{ { 500, 300}, 0, 0.09f };

	engine->Get<smile::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<smile::Renderer>());
	scene->Draw(engine->Get<smile::Renderer>());

	switch (state)
	{
	case Game::eState::Title:
		engine->Get<smile::Renderer>()->Draw(smile, transform);
		transform.position = { 250 , 300 };
		transform.scale = 1.0f;
		engine->Get<smile::Renderer>()->Draw(titleText, transform);
		transform.position = { 400, 500 };
		transform.scale = 0.25f;
		engine->Get<smile::Renderer>()->Draw(titleStart, transform);
	
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		transform.position = { 400, 300};
		transform.scale = 0.25f;
		engine->Get<smile::Renderer>()->Draw(gameOverText, transform);
		break;
	default:
		break;
	}


	engine->Get<smile::Renderer>()->EndFrame();
	/*graphics.SetColor(smile::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());*/


}



void Game::OnAddPoints(const smile::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const smile::Event& event)
{
	lives--;
	stateTimer = 0;
	state = (lives == 0) ? eState::GameOver : eState::PlayerDead;
}
