#pragma once

#include "../Renderer2DComponent.h"
#include "../../../../Animations/2D/SpriteSheet2DAnimation.h"

class SpriteSheet2DRendererComponent : public Renderer2DComponent
{
public:
	SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath);

protected:
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

private:
	SpriteSheet2DAnimation* IdleAnimation;
};