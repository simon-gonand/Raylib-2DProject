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

	ObjectGroupInfo Collisions = TileMapOwner->GetObjectGroup("Collisions");
	for (ObjectInfo* Object : Collisions.Objects)
	{
		Vector2 ObjectDrawLocation = Vector2Add(DrawLocation, Object->Location);
		if (EllipseObjectInfo* EllipseObject = dynamic_cast<EllipseObjectInfo*>(Object))
		{
			ObjectDrawLocation.x = ObjectDrawLocation.x + EllipseObject->Size.x / 2;
			ObjectDrawLocation.y = ObjectDrawLocation.y + EllipseObject->Size.y / 2;
			DrawEllipse(ObjectDrawLocation.x, ObjectDrawLocation.y, EllipseObject->Size.x / 2, EllipseObject->Size.y / 2, RED);
		}
		else if (RectangleObjectInfo* RectangleObject = dynamic_cast<RectangleObjectInfo*>(Object))
		{
			Rectangle ObjectDrawRectangle
			{
				ObjectDrawLocation.x,
				ObjectDrawLocation.y,
				RectangleObject->Size.x,
				RectangleObject->Size.y
			};

			DrawRectanglePro(ObjectDrawRectangle, { TileSize.x / 2, -TileSize.y / 2 }, 0.0f, BLUE);
		}
		else if (PolygoneObjectInfo* PolygonObject = dynamic_cast<PolygoneObjectInfo*>(Object))
		{
			for (int index = 0; index < PolygonObject->Points.size(); ++index)
			{
				Vector2 StartPoint = Vector2Add(ObjectDrawLocation, PolygonObject->Points[index]);
				Vector2 EndPoint = Vector2Add(ObjectDrawLocation, index == PolygonObject->Points.size() - 1 ? PolygonObject->Points[0] : PolygonObject->Points[index + 1]);
				DrawLine(StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y, YELLOW);
			}
		}
	}
}
