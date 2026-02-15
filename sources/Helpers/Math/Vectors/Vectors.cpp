#include "Vectors.h"

#include <raymath.h>

Vector2 Vector::Vector3ToVector2(Vector3 Vector)
{
    return Vector2({ Vector.x, Vector.y });
}

Vector3 Vector::Vector2ToVector3(Vector2 Vector)
{
    return Vector3({ Vector.x, Vector.y });
}