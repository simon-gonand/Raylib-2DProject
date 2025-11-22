#include "TileMap.h"

#include "../../Components/Renderer/2DRenderer/TileMapRenderer/TileMapRendererComponent.h"
#include "../../Helpers/XMLParser/XMLHelper.h"
#include "../../../external/rapidxml-1.13/rapidxml_utils.hpp"

#include <iostream>
#include <string>

TileMap::TileMap(const Vector2& InTileSize): TileSize{InTileSize}
{
}

TileMap::TileMap(const char* InTSXFilePath)
{
	rapidxml::file<> TileMapFile(InTSXFilePath);
	rapidxml::xml_document<> TileMapDocument;
	TileMapDocument.parse<0>(TileMapFile.data());
	rapidxml::xml_node<>* MapNode = TileMapDocument.first_node("map");
	if (!MapNode)
		return;
		
	//Tile Size
	TileSize = { XMLHelper::GetFloatAttribute(MapNode, "tilewidth"), XMLHelper::GetFloatAttribute(MapNode, "tileheight") };
	
	//Tile Sheets
	FillTileSheets(MapNode);
	
	//Layers
	FillLayers(MapNode);
}

void TileMap::Initialize()
{
	Actor::Initialize();

	RendererComp = std::make_shared<TileMapRendererComponent>(shared_from_this());
	AddComponent(RendererComp);

	SetActorLocation({0.0f});
	SetActorRotation(QuaternionIdentity());
	SetActorScale({ 1.0f, 1.0f });

	//FillTest();
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

void TileMap::FillTileSheets(rapidxml::xml_node<>* InMapNode)
{
	for (rapidxml::xml_node<>* TileSet = InMapNode->first_node("tileset"); TileSet; TileSet = TileSet->next_sibling("tileset"))
	{
		int FirstId = XMLHelper::GetIntAttribute(TileSet, "firstgid") - 1;
		rapidxml::xml_attribute<>* TileSetFileName = TileSet->first_attribute("source");
		if (!TileSetFileName)
			continue;

		rapidxml::file<> TileSetFile(TileSetFileName->value());
		rapidxml::xml_document<> TileSetDocument;
		TileSetDocument.parse<0>(TileSetFile.data());
		rapidxml::xml_node<>* TileSetNode = TileSetDocument.first_node("tileset");
		if (!TileSetNode)
			continue;

		Texture2D TileSheetTexture = GetTileSheetTexture(TileSetNode);
		std::vector<Rectangle> TileSheetRectangle;
		GetTileSheetRectangles(TileSetNode, TileSheetRectangle);
		Sheets.push_back({
				TileSheetTexture,
				(uint16_t)FirstId,
				TileSheetRectangle
			});
	}
}

Texture2D TileMap::GetTileSheetTexture(rapidxml::xml_node<>* InTileSetNode) const
{
	rapidxml::xml_node<>* ImageNode = InTileSetNode->first_node("image");
	if (!ImageNode)
		return Texture2D();

	rapidxml::xml_attribute<>* TexturePath = ImageNode->first_attribute("source");
	if (!TexturePath)
		return Texture2D();

	return LoadTexture(TexturePath->value());
}

void TileMap::GetTileSheetRectangles(rapidxml::xml_node<>* InTileSetNode, std::vector<Rectangle>& OutRectangles) const
{
	if (!InTileSetNode)
		return;
	 
	int Margin = XMLHelper::GetIntAttribute(InTileSetNode, "margin");
	int TileCount = XMLHelper::GetIntAttribute(InTileSetNode, "tilecount");
	int Columns = XMLHelper::GetIntAttribute(InTileSetNode, "columns");

	rapidxml::xml_node<>* ImageNode = InTileSetNode->first_node("image");
	if (!ImageNode)
		return;

	int Height = XMLHelper::GetIntAttribute(ImageNode, "height");
	int Width = XMLHelper::GetIntAttribute(ImageNode, "width");

	for (float y = Margin; y < Height; y += TileSize.y) 
	{
		for (float x = Margin; x < Width; x += TileSize.x)
		{
			OutRectangles.push_back({
				x,
				y,
				TileSize.x,
				TileSize.y
				});
		}
	}
}

void TileMap::FillLayers(rapidxml::xml_node<>* InMapNode)
{
	int MapHeight = XMLHelper::GetIntAttribute(InMapNode, "height");
	int MapWidth = XMLHelper::GetIntAttribute(InMapNode, "width");
	for (rapidxml::xml_node<>* Layer = InMapNode->first_node("layer"); Layer; Layer = Layer->next_sibling("layer"))
	{
		rapidxml::xml_node<>* LayerData = Layer->first_node("data");
		if (!LayerData)
			continue;

		unsigned int Size = 0;

		LayerInfo NewLayer;
		std::string LayerContent = LayerData->value();
		size_t LineFirstIndex = 0;
		int X = 0;
		int Y = 0;
		while (LineFirstIndex < LayerContent.size() && LineFirstIndex != std::string::npos)
		{
			X = 0;
			size_t LineLastIndex = LayerContent.find_first_of('\n', LineFirstIndex);
			if (LineLastIndex == std::string::npos)
				LineLastIndex = LayerContent.size();

			std::string LineContent = LayerContent.substr(LineFirstIndex, LineLastIndex - LineFirstIndex);
			LineFirstIndex = LineLastIndex + 1;
			size_t ColumnFirstIndex = 0;
			while (ColumnFirstIndex < LineContent.size() && ColumnFirstIndex != std::string::npos)
			{
				size_t ColumnLastIndex = LineContent.find_first_of(',', ColumnFirstIndex);
				if (ColumnLastIndex == std::string::npos || ColumnLastIndex == LineContent.size() - 1)
					ColumnLastIndex = LineContent.size();

				std::string Value = LineContent.substr(ColumnFirstIndex, ColumnLastIndex - ColumnFirstIndex);
				if (Value.empty() || Value[0] == '0' || Value == "\r" || Value == "\n")
				{
					if (Value == "0")
						++X;
					ColumnFirstIndex = ColumnLastIndex + 1;
					continue;
				}

				TileInfo& NewTile = NewLayer.Tiles.emplace_back();
				NewTile.TileIndex = static_cast<uint32_t>(std::atoll(Value.c_str())) - 1;
				NewTile.Location = {X * 16.0f, Y * 16.0f};
				ColumnFirstIndex = ColumnLastIndex + 1;
				++X;
			}
			++Y;
		}
		
		Layers.push_back(NewLayer);
	}
}

char* TileMap::TestDecode(const char* source, unsigned int* rlength)
{
	char* res, v;
	short j;
	unsigned int i;
	unsigned int in = 0;
	unsigned int src_len = (unsigned int)(strlen(source));

	*rlength = (src_len / 4) * 3;
	res = (char*)MemAlloc(*rlength);

	for (i = 0; i < src_len; i += 4) {
		in = 0;

		for (j = 0; j < 4; j++) {
			v = b64_value(source[i + j]);
			in = in << 6u;
			in += v; /* add 6b */
		}
		for (j = 0; j < 3; j++) {
			memcpy(res + (i / 4) * 3 + j, ((char*)&in) + 2 - j, 1); /* copy 3 bytes in reverse order */
		}
	}

	if (source[src_len - 1] == '=') {
		(*rlength)--;
	}
	if (source[src_len - 2] == '=') {
		(*rlength)--;
	}

	return res;
}

char TileMap::b64_value(char c)
{
	if (c >= 'A' && c <= 'Z') {
		return c - 'A';
	}
	else if (c >= 'a' && c <= 'z') {
		return c - 'a' + 26;
	}
	else if (c >= '0' && c <= '9') {
		return c - '0' + 52;
	}
	else if (c == '+') {
		return 62;
	}
	else if (c == '/') {
		return 63;
	}
	else if (c == '=') {
		return 0;
	}
	return -1;
}
