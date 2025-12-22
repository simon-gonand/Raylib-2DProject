#include "TileMapRendererComponent.h"

#include "../../../../Helpers/Math/Vectors/Vectors.h"
#include "../../../../Managers/Camera/CameraManager.h"

TileMapRendererComponent::TileMapRendererComponent(std::shared_ptr<Actor> Owner, bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize):
	Renderer2DComponent(Owner, "", bAutoActivate, InLocation, InRotation, InScale, InSize)
{
	if (Owner && typeid(*Owner) == typeid(TileMap)) {
		TileMapOwner = std::static_pointer_cast<TileMap>(Owner);
		Size = TileMapOwner->GetTileSize();
	}
}

void TileMapRendererComponent::Initialize()
{
	const Camera2D& UsedCamera = CameraManager::Get()->GetCameraToUse();
	InitialCameraLocation = UsedCamera.target;
}

void TileMapRendererComponent::Update(float DeltaTime)
{
	ComponentBase::Update(DeltaTime);

	if (!TileMapOwner)
		return;

	Vector2 DrawLocation = Vector::Vector3ToVector2(GetWorldLocation());
	Quaternion DrawRotation = GetWorldRotation();
	Vector2 TileSize = GetSizeScaledWithRatio();

	DrawBackground(DrawLocation, DrawRotation, TileSize);
	DrawTiles(DrawLocation, DrawRotation, TileSize);
}

void TileMapRendererComponent::DrawBackground(const Vector2& DrawLocation, const Quaternion& DrawRotation, const Vector2& DrawScale)
{
	const Camera2D& UsedCamera = CameraManager::Get()->GetCameraToUse();
	const Vector2 TileMapPxlSize = TileMapOwner->GetPxlTileMapSize();
	for (const BackgroundImageInfo& Image : TileMapOwner->GetBackgroundImages())
	{
		Vector2	CameraOffset = Vector2Subtract(InitialCameraLocation, UsedCamera.target);
		CameraOffset = Vector2Multiply(CameraOffset, Vector2Subtract(Vector2One(), Image.ParallaxScrollingFactor));
		int ImageXIndex = Image.RepeatX ? -2 : -1;
		int ImageYIndex = Image.RepeatY ? -2 : -1;
		do
		{
			++ImageYIndex;
			do
			{
				++ImageXIndex;
				Rectangle Source
				{
					0.0f,
					0.0f,
					Image.Texture.width,
					Image.Texture.height
				};

				Rectangle Destination
				{
					(DrawLocation.x + Image.Texture.width * ImageXIndex) - CameraOffset.x,
					(DrawLocation.y + Image.Texture.height * ImageYIndex) - CameraOffset.y,
					Image.Texture.width,
					Image.Texture.height
				};

				DrawTexturePro(Image.Texture, Source, Destination, { 0.0f, 0.0f }, DrawRotation.x, WHITE);
			} while (Image.RepeatX && DrawLocation.x + Image.Texture.width * ImageXIndex < TileMapPxlSize.x);
		} while (Image.RepeatY && DrawLocation.y + Image.Texture.height * ImageYIndex < TileMapPxlSize.y);
	}
}

void TileMapRendererComponent::DrawTiles(const Vector2& DrawLocation, const Quaternion& DrawRotation, const Vector2& DrawScale)
{
	for (const LayerInfo& Layer : TileMapOwner->GetLayers())
	{
		for (const TileInfo& Tile : Layer.Tiles)
		{
			TileSheetTileInfo SheetTileInfo = TileMapOwner->GetTileSheetInfoForTile(Tile);
			Vector2 TileDrawLocation = Vector2Add(DrawLocation, Tile.Location);

			Rectangle DrawTileDestination
			{
				TileDrawLocation.x,
				TileDrawLocation.y,
				DrawScale.x,
				DrawScale.y
			};
			DrawTexturePro(*SheetTileInfo.Texture, SheetTileInfo.Source, DrawTileDestination, { 0.0f, DrawScale.y }, DrawRotation.x, WHITE);
		}
	}
}
