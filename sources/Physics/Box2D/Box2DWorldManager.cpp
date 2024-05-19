#include "Box2DWorldManager.h"

Box2DWorldManager::Box2DWorldManager()
{
}

void Box2DWorldManager::Initialize(Vector3 InGravity)
{
	b2Vec2 Gravity = b2Vec2(InGravity.x, InGravity.y);
	World = new b2World(Gravity);
}
