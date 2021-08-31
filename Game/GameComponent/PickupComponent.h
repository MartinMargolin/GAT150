#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"


class PickupComponent : public smile::Component
{
public:
	virtual ~PickupComponent();

	std::unique_ptr<Object> Clone() const { return std::make_unique<PickupComponent>(*this); }

	void Create() override;
	virtual void Update() override;

	void OnCollisionEnter(const smile::Event& event);
	void OnCollisionExit(const smile::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	int scoreValue{ 0 };

private:
	std::list<smile::Actor*> contacts;



}; 
