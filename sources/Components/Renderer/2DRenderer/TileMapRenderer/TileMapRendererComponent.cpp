#include "TileMapRendererComponent.h"

#include "../../../../Helpers/Math/Vectors/Vectors.h"

TileMapRendererComponent::TileMapRendererComponent(std::shared_ptr<Actor> Owner, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize):
	Renderer2DComponent(Owner, "", InLocation, InRotation, InScale, InSize)
{
	if (Owner && typeid(*Owner) == typeid(TileMap)) {
		TileMapOwner = std::static_pointer_cast<TileMap>(Owner);
		Size = TileMapOwner->GetTileSize();
	}
}

void TileMapRendererComponent::Update(float DeltaTime)
{
	if (!TileMapOwner)
		return;

	Vector2 DrawLocation = Vector::Vector3ToVector2(GetWorldLocation());
	Quaternion DrawRotation = GetWorldRotation();
	Vector2 TileSize = GetSizeScaledWithRatio();
	for (LayerInfo Layer : TileMapOwner->GetLayers())
	{
		for (TileInfo Tile : Layer.Tiles)
		{
			TileSheetTileInfo SheetTileInfo = TileMapOwner->GetTileSheetInfoForTile(Tile);
			Vector2 TileDrawLocation = Vector2Add(DrawLocation, Tile.Location);

			Rectangle DrawTileDestination
			{
				TileDrawLocation.x,
				TileDrawLocation.y,
				TileSize.x,
				TileSize.y
			};
			DrawTexturePro(*SheetTileInfo.Texture, SheetTileInfo.Source, DrawTileDestination, { TileSize.x / 2, TileSize.y / 2 }, DrawRotation.x, WHITE);
		}
	}
}
