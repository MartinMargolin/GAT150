#include "SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Object/Actor.h"
#include "Engine.h"
namespace smile
{
	void SpriteComponent::Update()
	{

	}

	void SpriteComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, rect, owner->transform);
	}
	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string texturename;
		JSON_READ(value, texturename);
		JSON_READ(value, rect);

		texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>(texturename, owner->scene->engine->Get<Renderer>());

		if (rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0)
		{
			Vector2 size = texture->GetSize();
			rect.w = static_cast<int>(size.x);
			rect.h = static_cast<int>(size.y);
		}

		return true;
	}
}