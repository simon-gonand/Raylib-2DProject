#include "Actor.h"

#include <raymath.h>

#include "../../Components/BaseClass/ComponentBase.h"
#include <iostream>

Actor::Actor()
{
}

void Actor::Initialize()
{
}

void Actor::AddComponent(std::shared_ptr<ComponentBase> Component)
{
	Components.push_back(Component);
	Component->Initialize();
}

void Actor::RemoveComponent(std::shared_ptr<ComponentBase> Component)
{
	Components.remove(Component);
}

const std::list<std::shared_ptr<ComponentBase>>& Actor::GetAllComponents() const
{
	return Components;
}

const Transform& Actor::GetActorTransform() const
{
	return ActorTransform;
}

const Vector3& Actor::GetActorLocation() const
{
	return ActorTransform.translation;
}

const Quaternion& Actor::GetActorRotation() const
{
	return ActorTransform.rotation;
}

const Vector3& Actor::GetActorScale() const
{
	return ActorTransform.scale;
}

void Actor::SetActorLocation(const Vector3& NewLocation)
{
	ActorTransform.translation = NewLocation;
	for (DelegateBase<void, const Vector3&>* Delegate : OnLocationSet)
	{
		Delegate->Invoke(NewLocation);
	}
}

void Actor::AddActorLocation(const Vector3& AddedLocation)
{
	ActorTransform.translation = Vector3Add(ActorTransform.translation, AddedLocation);
	for (DelegateBase<void, const Vector3&>* Delegate : OnLocationSet)
	{
		Delegate->Invoke(ActorTransform.translation);
	}
}

void Actor::SetActorRotation(const Quaternion& NewRotation)
{
	ActorTransform.rotation = NewRotation;
	for (DelegateBase<void, const Quaternion&>* Delegate : OnRotationSet)
	{
		Delegate->Invoke(NewRotation);
	}
}

void Actor::SetActorScale(const Vector3& NewScale)
{
	ActorTransform.scale = NewScale;
}

void Actor::Update(float Tick)
{
	for (std::shared_ptr<ComponentBase> Component : Components) 
	{
		if (Component)
			Component->Update(Tick);
	}
}

Vector2 Actor::GetLocationToDraw(const Vector2& ScreenSize)
{
	Vector3 DrawWorldLocation = Vector3RotateByQuaternion(GetActorLocation(), GetActorRotation());
	//std::cout << "Location: " << DrawWorldLocation.x << "; " << DrawWorldLocation.y << "; " << DrawWorldLocation.z << std::endl;
	Vector2 DrawLocation = ConvertWorldToScreen({ DrawWorldLocation.x, DrawWorldLocation.y }, ScreenSize);
	DrawLocation.x -= ActorTransform.scale.x / 2;
	DrawLocation.y -= ActorTransform.scale.y / 2;
	return DrawLocation;
}

void Actor::Draw(const Vector2& ScreenSize)
{
}

// Convertion calculation get from github of box2d on how to link box2d and raylib together
// https://github.com/erincatto/box2d-raylib/blob/main/main.c
Vector2 Actor::ConvertWorldToScreen(const Vector2& WorldCoordinates, const Vector2& ScreenSize)
{
	Vector2 result = { WorldCoordinates.x + 0.5f * ScreenSize.x, 0.5f * ScreenSize.y - WorldCoordinates.y };
	return result;
}
