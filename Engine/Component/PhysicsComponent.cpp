#include "..\PhysicsComponent.h"
#include "Engine.h"
namespace smile
{

void PhysicsComponent::Update()
{

	velocity += accelleration * owner->scene->engine->time.deltaTime;
	owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
	velocity *= damping;

	accelleration = Vector2::zero;
}

bool PhysicsComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PhysicsComponent::Read(const rapidjson::Value& value)
{

	JSON_READ(value, damping);
	return true;
}


}
