#pragma once

#include "../BaseClass/Actor.h"

#include "../../../external/rapidxml-1.13/rapidxml.hpp"

#include <vector>
#include <memory>
#include <string>

#include "../../Helpers/XMLParser/XMLHelper.h"
#include "../../Helpers/Globals/Globals.h"

struct TileInfo
{
	Vector2 Location;
	uint32_t TileIndex;
};

struct LayerInfo
{
	std::vector<TileInfo> Tiles;
};

struct ObjectInfo
{
	char* Name;
	Vector2 Location;

	virtual void FillInformation(rapidxml::xml_node<>* InObjectNode)
	{
		const char* ObjectName = XMLHelper::GetStringAttribute(InObjectNode, "name");
		Name = (char*)malloc(sizeof(ObjectName));
		strcpy(Name, ObjectName);
		float XLocation = XMLHelper::GetFloatAttribute(InObjectNode, "x");
		float YLocation = XMLHelper::GetFloatAttribute(InObjectNode, "y");
		Location = { XLocation, YLocation };
	}
};

struct RectangleObjectInfo : public ObjectInfo
{
	Vector2 Size;

	virtual void FillInformation(rapidxml::xml_node<>* InObjectNode) override
	{
		ObjectInfo::FillInformation(InObjectNode);
		float Width = XMLHelper::GetFloatAttribute(InObjectNode, "width");
		float Height = XMLHelper::GetFloatAttribute(InObjectNode, "height");
		Size = { Width, Height };
	}
};

struct EllipseObjectInfo : public RectangleObjectInfo
{
};

struct PolygoneObjectInfo : public ObjectInfo
{
	std::vector<Vector2> Points;

	virtual void FillInformation(rapidxml::xml_node<>* InObjectNode) override
	{
		ObjectInfo::FillInformation(InObjectNode);
		rapidxml::xml_node<>* PolygonNode = InObjectNode->first_node("polygon");
		if (PolygonNode)
		{
			std::string PointsStr = XMLHelper::GetStringAttribute(PolygonNode, "points");
			std::vector<std::string> PointsStrArray;
			StringHelper::ParseIntoArray(PointsStrArray, PointsStr, ' ');
			for(const std::string& PointStr : PointsStrArray)
			{
				std::vector<std::string> PointStrArray;
				StringHelper::ParseIntoArray(PointStrArray, PointStr, ',');
				if (PointStrArray.size() == 2)
				{
					Points.push_back({(float)atof(PointStrArray[0].c_str()), (float)atof(PointStrArray[1].c_str())});
				}
			}
		}
	}
};

struct ObjectGroupInfo 
{
	char* Name;
	std::vector<ObjectInfo*> Objects;
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
	TileMap(const char* InTSXFilePath);

	virtual void Initialize() override;

	const Vector2& GetTileSize() const;

	const std::vector<LayerInfo>& GetLayers() const;
	const ObjectGroupInfo& GetObjectGroup(const char* InObjectGroupName) const;

	TileSheetTileInfo GetTileSheetInfoForTile(const TileInfo& InTile);

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::string TSXDirectoryPath;

	Vector2 TileSize;
	std::vector<TileSheet> Sheets;
	std::vector<LayerInfo> Layers;
	std::vector<ObjectGroupInfo> ObjectGroups;

	std::shared_ptr<class TileMapRendererComponent> RendererComp;

	std::vector<std::shared_ptr<class PhysicsComponent>> PhysicsComps;

	TileSheet* LastUsedTileSheet = nullptr;

	void FillTileSheets(rapidxml::xml_node<>* InMapNode);
	Texture2D GetTileSheetTexture(rapidxml::xml_node<>* InTileSetNode) const;
	void GetTileSheetRectangles(rapidxml::xml_node<>* InTileSetNode, std::vector<Rectangle>& OutRectangles) const;

	void FillLayers(rapidxml::xml_node<>* InMapNode);

	void FillObjects(rapidxml::xml_node<>* InMapNode);
	ObjectInfo* GetObjectInfoType(rapidxml::xml_node<>* InObjectNode);

	void InitializeColliders();

	char* TestDecode(const char* source, unsigned int* rlength);
	char b64_value(char c);
};