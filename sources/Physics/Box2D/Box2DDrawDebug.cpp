#include "Box2DDrawDebug.h"

#include <raylib.h>

#include "../../Helpers/Globals/Globals.h"

Box2DDrawDebug::Box2DDrawDebug(): b2Draw()
{
}

void Box2DDrawDebug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2 StartVertex = vertices[i];
        b2Vec2 EndVertex = i == vertexCount - 1 ? vertices[0] : vertices[i + 1];
        DrawLineEx({ StartVertex.x * PTM_RATIO, StartVertex.y * PTM_RATIO }, { EndVertex.x * PTM_RATIO, EndVertex.y * PTM_RATIO }, 1.0f, ConvertToColor(color));
    }
}

void Box2DDrawDebug::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    DrawSolidPolygon(vertices, vertexCount, color);
}

void Box2DDrawDebug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    DrawCircleV({ center.x * PTM_RATIO, center.y * PTM_RATIO }, radius * PTM_RATIO, ConvertToColor(color));
}

void Box2DDrawDebug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    DrawCircle(center, radius, color);
}

void Box2DDrawDebug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    Vector2 P1 = { p1.x * PTM_RATIO, p1.y * PTM_RATIO};
    Vector2 P2 = { p2.x * PTM_RATIO, p2.y * PTM_RATIO};
    DrawLineEx(P1, P2, 2.0f, ConvertToColor(color));
}

void Box2DDrawDebug::DrawTransform(const b2Transform& xf)
{
    DrawCircleV({ xf.p.x * PTM_RATIO, xf.p.y * PTM_RATIO }, 1.5f, ORANGE);
}

void Box2DDrawDebug::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    DrawCircleV({ p.x * PTM_RATIO, p.y * PTM_RATIO }, 1.5f, ConvertToColor(color));
}

Color Box2DDrawDebug::ConvertToColor(const b2Color& color)
{
    Color DrawColor = {
        color.r * 255.0f,
        color.g * 255.0f,
        color.b * 255.0f,
        color.a * 255.0f
    };

    return DrawColor;
}
