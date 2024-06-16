#pragma once

#include <list>
#include <memory>
#include "raylib.h"
#include <vector>

#include "../../Utils/Delegates/DelegateBase/DelegateBase.h"

class Actor: public std::enable_shared_from_this<Actor>
{
private:
	std::list<std::shared_ptr<class ComponentBase>> Components;

	Transform ActorTransform; // Will be stored in a Root Component ?
	
public:
	Actor();
	virtual ~Actor(){}

	virtual void Initialize();

	void AddComponent(std::shared_ptr<ComponentBase> Component);
	void RemoveComponent(std::shared_ptr<ComponentBase> Component);
	const std::list<std::shared_ptr<ComponentBase>>& GetAllComponents() const;

	const Transform& GetActorTransform() const;
	const Vector3& GetActorLocation() const;
	const Quaternion& GetActorRotation() const;
	const Vector3& GetActorScale() const;

	void SetActorLocation(const Vector3& NewLocation);
	void AddActorLocation(const Vector3& AddedLocation);
	void SetActorRotation(const Quaternion& NewRotation);
	void SetActorScale(const Vector3& NewScale);

	virtual void Update(float Tick);
	virtual void Draw(const Vector2& ScreenSize);

	// Event Bindings
	template<class C, void (C::* Function)(const Vector3&)>
	void BindOnLocationSet(C* Instance)
	{
		DelegateBase<void, const Vector3&>* OnLocationSetDelegate = new DelegateBase<void, const Vector3&>();
		OnLocationSetDelegate->Bind<C, Function>(Instance);
		OnLocationSet.push_back(OnLocationSetDelegate);
	}

protected:
	Vector2 ConvertWorldToScreen(const Vector2& WorldCoordinates, const Vector2& ScreenSize);

private:
	// Events
	std::vector<DelegateBase<void, const Vector3&>*> OnLocationSet;
};

