#pragma once

#include <raylib.h>

#include "../BaseClass/ComponentBase.h"

class CameraComponent : public ComponentBase, public std::enable_shared_from_this<CameraComponent>
{

protected:
	Camera2D Camera;

public:
	CameraComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true,
		const Vector2& InitialPos = { 0.0f }, const Vector2& Offset = { 0.0f }, const float& Rotation = 0.0f, const float& Zoom = 1.0f);
	~CameraComponent();

	void SwithToThisCamera();

	const Camera2D& GetCamera() const;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
};