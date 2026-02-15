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

Vector3 Vector::Vector3InterpTo(const Vector3& Current, const Vector3& Target, float DeltaTime, float InterpSpeed) // Based on Unreal Engine 5 VInterpTo function
{
    if (InterpSpeed <= 0.0f)
        return Target;

    const Vector3 Distance = Vector3Subtract(Target, Current);
    if (Vector3Length(Distance) < 0.001f)
        return Target;

    const Vector3 DeltaMove = Vector3Scale(Distance, Clamp(DeltaTime * InterpSpeed, 0.0f, 1.0f));
    return Vector3Add(Current, DeltaMove);
}

Vector2 Vector::Vector2InterpTo(const Vector2& Current, const Vector2& Target, float DeltaTime, float InterpSpeed)
{
    if (InterpSpeed <= 0.0f)
        return Target;

    const Vector2 Distance = Vector2Subtract(Target, Current);
    if (Vector2Length(Distance) < 0.001f)
        return Target;

    const Vector2 DeltaMove = Vector2Scale(Distance, Clamp(DeltaTime * InterpSpeed, 0.0f, 1.0f));
    return Vector2Add(Current, DeltaMove);
}
