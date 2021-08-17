#pragma once
#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

class Game
{
public:
	enum class eState
	{
		Title, 
		StartGame,
		StartLevel,
		Game, 
		PlayerDead,
		GameOver
	};
	

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool isQuit() { return quit; }

private:

	void OnAddPoints(const smile::Event& event);
	void OnPlayerDead(const smile::Event& event);

public: 
	std::unique_ptr<smile::Engine> engine;
	std::unique_ptr<smile::Scene> scene;
	
private: 

	bool quit = false;

	eState state = eState::Title;
	float stateTimer = 0.0f;
	float spawnTimer = 0.0f;


	size_t score = 0;
	size_t lives = 0;

	smile::AudioChannel musicChannel;
	std::shared_ptr<smile::Texture> smile;
	std::shared_ptr<smile::Texture> ship;
	std::shared_ptr<smile::Texture> particleTexture;
	std::shared_ptr<smile::Texture> titleText;
	std::shared_ptr<smile::Texture> titleStart;
	std::shared_ptr<smile::Texture> gameOverText;
	std::unique_ptr<smile::Actor> actor;
};