#include "..\PhysicsComponent.h"
#include "Engine.h"
namespace smile
{

void PhysicsComponent::Update()
{
	velocity += accelleration * owner->scene->engine->time.deltaTime;
	owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
}


}
