#pragma once

#include "../BaseClass/Actor.h"

#include <vector>
#include <memory>

struct TileInfo
{
	Vector2 Location;
	uint16_t TileIndex;
};

struct LayerInfo
{
	std::vector<TileInfo> Tiles;
};

struct TileSheetTileInfo
{
	Texture2D* Texture;
	Rectangle Source;
};

struct TileSheet
{
	Texture2D Texture;
	uint16_t StartTileIndex;
	std::vector<Rectangle> TileSourceRectangle;

	bool HasIndex(uint16_t Index) const {
		return Index >= StartTileIndex && Index < StartTileIndex + TileSourceRectangle.size();
	}
};

class TileMap : public Actor
{
public:
	TileMap(const Vector2& InTileSize);

	virtual void Initialize() override;

	const Vector2& GetTileSize() const;

	const std::vector<LayerInfo>& GetLayers() const;

	TileSheetTileInfo GetTileSheetInfoForTile(const TileInfo& InTile);

protected:
	virtual void Update(float DeltaTime) override;

private:
	Vector2 TileSize;
	std::vector<TileSheet> Sheets;
	std::vector<LayerInfo> Layers;

	std::shared_ptr<class TileMapRendererComponent> RendererComp;

	TileSheet* LastUsedTileSheet = nullptr;

	void FillTest();
};