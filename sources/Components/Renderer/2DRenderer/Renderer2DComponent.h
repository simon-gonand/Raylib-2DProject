#pragma once

#include "../RendererComponent.h"

class Renderer2DComponent : public RendererComponent
{
public:
	Renderer2DComponent(std::shared_ptr<Actor> Owner, const char* TexturePath);

protected:
	Texture2D DefaultTexture2D;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

private:
	const char* DefaultTexturePath;
};