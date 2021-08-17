#pragma once
#include "Object/Actor.h"

class Enemy : public smile::Actor
{
public:
	Enemy(const smile::Transform& transform, std::shared_ptr<smile::Texture> texture, float speed) : smile::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;


private:
	float speed{ 300 };
	float fireTimer{ 0 };
	float fireRate{ 2.0f };
};