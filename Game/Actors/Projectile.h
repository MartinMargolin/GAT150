
#pragma once
#include "Object/Actor.h"

class Projectile : public smile::Actor
{
public:
	Projectile(const smile::Transform& transform, std::shared_ptr<smile::Texture> texture, float speed) : smile::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 1 };

	float speed{ 250 };
};