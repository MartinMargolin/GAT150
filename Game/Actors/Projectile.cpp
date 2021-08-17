#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += smile::Vector2::Rotate(smile::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = smile::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = smile::Wrap(transform.position.y, 0.0f, 600.0f);

	std::vector<smile::Color> colors = { smile::Color::white, smile::Color::red };
	/*scene->engine->Get<smile::ParticleSystem>()->Create(transform.position, 3, 0.5f, smile::Color::white, 10);*/
}
