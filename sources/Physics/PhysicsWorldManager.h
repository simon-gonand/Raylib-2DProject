#pragma once

#include <raylib.h> // Must Include raylib before raymath to avoid Vector struct redefinitions
#include <raymath.h>

#include <memory>

enum PhysicsEngineType 
{
	BOX2D
};

struct RaycastResult
{
	bool bHasHit = false;;
	Vector3 HitLocation = { 0.0f };
	class Actor* HitActor = nullptr;
	Vector3 Normal = { 0.0f };
};

class PhysicsWorldManager
{
private:
	static std::shared_ptr<PhysicsWorldManager> Instance;

	static PhysicsEngineType EngineType;

	PhysicsWorldManager(PhysicsWorldManager& InPhysicsWorldManager) = delete;
	void operator=(const PhysicsWorldManager& InPhysicsWorldManager) = delete;
	
protected:
	PhysicsWorldManager();

	bool bDebugMode;

public:
	static void SetPhysicsEngineType(PhysicsEngineType InEngineType);
	static std::shared_ptr<PhysicsWorldManager> Get();

	virtual void Initialize(const Vector3& InGravity) = 0;
	virtual void Update(float DeltaTime) = 0;

	virtual void DrawDebug() = 0;
	void SetDebugMode(bool bInDebug);

	virtual RaycastResult Raycast(Vector3 StartLocation, Vector3 EndLocation) = 0;
	virtual void* CreateDistanceJointBetween(std::shared_ptr<class PhysicsComponent> PhysicsCompA, std::shared_ptr<PhysicsComponent> PhysicsCompB, const Vector3& AttachPointA, const Vector3& AttachPointB) = 0;
	virtual void DestroyJoint(void* Joint) = 0;
};