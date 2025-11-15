#include "TileMap.h"

#include "../../Components/Renderer/2DRenderer/TileMapRenderer/TileMapRendererComponent.h"

TileMap::TileMap(const Vector2& InTileSize): TileSize{InTileSize}
{
}

void TileMap::Initialize()
{
	Actor::Initialize();

	RendererComp = std::make_shared<TileMapRendererComponent>(shared_from_this());
	AddComponent(RendererComp);

	SetActorLocation({0.0f});
	SetActorRotation(QuaternionIdentity());
	SetActorScale({ 1.0f, 1.0f });

	FillTest();
}

const Vector2& TileMap::GetTileSize() const
{
	return TileSize;
}

const std::vector<LayerInfo>& TileMap::GetLayers() const
{
	return Layers;
}

TileSheetTileInfo TileMap::GetTileSheetInfoForTile(const TileInfo& InTile)
{
	if (!LastUsedTileSheet || !LastUsedTileSheet->HasIndex(InTile.TileIndex))
	{
		for (TileSheet& Sheet : Sheets)
		{
			if (&Sheet != LastUsedTileSheet && Sheet.HasIndex(InTile.TileIndex))
			{
				LastUsedTileSheet = &Sheet;
				break;
			}
		}
	}

	return {
		&LastUsedTileSheet->Texture,
		LastUsedTileSheet->TileSourceRectangle[InTile.TileIndex - LastUsedTileSheet->StartTileIndex]
	};
}

void TileMap::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
}

void TileMap::FillTest()
{
	Texture2D SheetTexture = LoadTexture("assets/TileMap/_Brown_Tile_Terrain.png");
	std::vector<Rectangle> SheetTileRectangles;
	SheetTileRectangles.push_back({
			16.0f,
			16.0f,
			TileSize.x,
			TileSize.y
		});
	Sheets.push_back({
			SheetTexture,
			0,
			SheetTileRectangles
		});

	std::vector<TileInfo> TileInfo;
	TileInfo.push_back({
			{0.0f},
			0
		});
	Layers.push_back({
			TileInfo
		});
}
