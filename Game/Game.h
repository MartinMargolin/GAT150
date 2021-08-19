#pragma once
#include "Engine.h"


class Game
{


public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool isQuit() { return quit; }


public:
	std::unique_ptr<smile::Engine> engine;
	std::unique_ptr<smile::Scene> scene;

private:

	bool quit = false;
};
