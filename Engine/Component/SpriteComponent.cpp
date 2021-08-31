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
		renderer->Draw(texture, owner->transform);
	}
	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string texturename;
		JSON_READ(value, texturename);

		texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>(texturename, owner->scene->engine->Get<Renderer>());

		return true;
	}
}