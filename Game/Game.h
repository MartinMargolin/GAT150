#pragma once
#include "Engine.h"


class Game
{
	enum class eState
	{
		Launch,
		Reset,
		Title,
		StartGame,
		StartLevel,
		Level,
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
	void Launch();
	void Reset();
	void Title();
	void StartGame();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();

	void OnAddScore(const smile::Event& event);
	void OnRemoveScore(const smile::Event& event);

public:
	std::unique_ptr<smile::Engine> engine;
	std::unique_ptr<smile::Scene> scene;

private:

	bool quit = false;
	bool loaded = false;

	eState state = eState::Launch;
	float stateTimer = 0;
	float spawnTimer = 0;
	int score = 0;

};
