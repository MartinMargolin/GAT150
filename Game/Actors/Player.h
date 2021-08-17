#pragma once
#include "Object/Actor.h"


class Player : public smile::Actor
{
public:

	Player(const smile::Transform& transform, std::shared_ptr<smile::Texture> texture, float speed); 

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed{ 300 };
	float fireTimer{ 0 };
	float fireRate{ 0.5f };
	smile::Vector2 velocity;
};
