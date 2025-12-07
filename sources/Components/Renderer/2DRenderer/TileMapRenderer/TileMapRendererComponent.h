#pragma once

#include "../Renderer2DComponent.h"
#include "../../../../Actors/TileMap/TileMap.h"

class TileMapRendererComponent : public Renderer2DComponent 
{
public:
	TileMapRendererComponent(std::shared_ptr<Actor> Owner, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f }, const Vector2& InSize = { 1.0f, 1.0f });

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<TileMap> TileMapOwner;

	void DrawBackground(const Vector2& DrawLocation, const Quaternion& DrawRotation, const Vector2& DrawScale);
	void DrawTiles(const Vector2& DrawLocation, const Quaternion& DrawRotation, const Vector2& DrawScale);
};