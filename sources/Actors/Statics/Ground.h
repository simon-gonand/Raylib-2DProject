#pragma once

#include "../BaseClass/Actor.h"

class Ground : public Actor
{
public:
	virtual void Initialize() override;

	virtual void Draw(const Vector2& ScreenSize) override;

private:
	std::shared_ptr<class PhysicsComponent> PhysicsComp;
	std::shared_ptr<class RendererComponent> RendererComp;
};

