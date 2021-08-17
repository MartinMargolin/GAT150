#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);
	if (scene->GetActor<Player>())
	{
		smile::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;

		smile::Vector2 forward = smile::Vector2::Rotate(smile::Vector2::right, transform.rotation);

		float turnAngle = smile::Vector2::SignedAngle(forward, direction.Normalized());
		//transform.rotation = smile::Lerp(transform.rotation = turnAngle, 5 * dt);

		transform.rotation = transform.rotation + turnAngle * (3 * dt);

		float angle = smile::Vector2::Angle(direction.Normalized(), forward);

		transform.position += smile::Vector2::Rotate(smile::Vector2::right, transform.rotation) * speed * dt;
		transform.position.x = smile::Wrap(transform.position.x, 0.0f, 800.0f);
		transform.position.y = smile::Wrap(transform.position.y, 0.0f, 600.0f);

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= smile::DegToRad(10))
		{


			fireTimer = fireRate;

			smile::Transform t = transform;
			t.scale = 0.2f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<smile::ResourceSystem>()->Get<smile::Texture>("playerShotRed.png", scene->engine->Get<smile::Renderer>()) , 300.0f);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));


		}
		}


	}


void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;

		destroy = true;	
		//scene->engine->Get<smile::ParticleSystem>()->Create(transform.position, 3, 0.5f, smile::Color::red, 10);
		//scene->engine->Get<smile::AudioSystem>()->PlayAudio("explosion");

		smile::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<smile::EventSystem>()->Notify(event);

	}
}
