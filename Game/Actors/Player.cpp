#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"
#include <vector>
#include <memory>

Player::Player(const smile::Transform& transform, std::shared_ptr<smile::Texture> texture, float speed) : smile::Actor{ transform, texture }, speed{ speed } 
{
}

void Player::Initialize()
{
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = smile::Vector2{ -4, 0 };
	locator->transform.localRotation = smile::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = smile::Vector2{ 4, 0 };
	AddChild(std::move(locator));


	/*
	std::unique_ptr wing = std::make_unique<Actor>(smile::Transform{} , scene->engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("wing.txt"));
	wing->transform.localPosition = smile::Vector2{ -0, 0 };
	AddChild(std::move(wing));
	*/
}

void Player::Update(float dt)	
{
	Actor::Update(dt);


	float thrust = 0;
	if (scene->engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == smile::InputSystem::eKeyState::HELD) transform.rotation -= 5 * dt;
	if (scene->engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == smile::InputSystem::eKeyState::HELD) transform.rotation += 5 * dt;
	if (scene->engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == smile::InputSystem::eKeyState::HELD) thrust = speed;
	if (scene->engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == smile::InputSystem::eKeyState::HELD) thrust = -speed;

	smile::Vector2 acceleration;
	acceleration += smile::Vector2::Rotate(smile::Vector2::right, transform.rotation) * thrust;
	//smile::Vector2 gravity = (smile::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	//smile::Vector2 gravity = smile::Vector2::down * 50;
	//acceleration += gravity;


	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.975f;

	transform.position.x = smile::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = smile::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && (scene->engine->Get<smile::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == smile::InputSystem::eKeyState::HELD))
	{
		fireTimer = fireRate;

		smile::Transform t = children[1]->transform;
		t.scale = 0.4f;
			
		std::unique_ptr<Projectile> projectile  = std::make_unique<Projectile>(t, scene->engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("playerShotRed.png", scene->engine->Get<smile::Renderer>()), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
		
		scene->engine->Get<smile::AudioSystem>()->PlayAudio("bruh", 1, 1.0f);
	}

	//std::vector<smile::Color> colors = { smile::Color::white, smile::Color::red };
	//scene->engine->Get<smile::ParticleSystem>()->Create(transform.position, 3, 2, colors, 10, children[0]->transform.rotation, smile::DegToRad(30));
}

void Player::OnCollision(Actor* actor)
{
	//return;

	if (dynamic_cast<Enemy*>(actor) /*dynamic_cast<Projectile*>(actor)->tag = "Enemy"*/)
	{

		destroy = true;
	//	scene->engine->Get<smile::ParticleSystem>()->Create(transform.position, 3, 0.5f, smile::Color::red, 10);
	//	scene->engine->Get<smile::AudioSystem>()->PlayAudio("playerdeath");

		smile::Event event;
		event.name = "PlayerDead";
		event.data = std::string("D:");
		scene->engine->Get<smile::EventSystem>()->Notify(event);

	}
}

