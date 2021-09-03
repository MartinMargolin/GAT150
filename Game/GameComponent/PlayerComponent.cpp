#include "PlayerComponent.h"
#include "Engine.h"

using namespace smile;

PlayerComponent::~PlayerComponent()
{
		owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
		owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);



	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "audio/hurt.wav");
}

void PlayerComponent::Update()
{

	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::HELD)
	{
		force.x -= speed;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::HELD)
	{
		force.x += speed;
	}

		if (contacts.size() > 0  && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::PRESSED)
	{
			force.y -= 200;
	}


	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
		assert(spriteAnimationComponent);


		if (physicsComponent->velocity.x > 0) spriteAnimationComponent->StartSequence("walk_right");
		else if (physicsComponent->velocity.x < 0) spriteAnimationComponent->StartSequence("walk_left");
		else spriteAnimationComponent->StartSequence("idle");


}

void PlayerComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Ground"))
	{
		contacts.push_back(actor);
	}

	if (istring_compare(actor->tag, "Enemy"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
		Event event;
		event.name = "remove_score";
		event.data = 5;
		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}

	std::cout << actor->tag << std::endl;
	
}

void PlayerComponent::OnCollisionExit(const Event& event)
{

}



bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}

