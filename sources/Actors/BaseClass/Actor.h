#pragma once

#include <memory>
#include "raylib.h"
#include <vector>
#include <list>

#include "../../Utils/Delegates/DelegateBase/DelegateBase.h"

class Actor: public std::enable_shared_from_this<Actor>
{
private:
	std::vector<std::shared_ptr<class ComponentBase>> Components;

	Transform ActorTransform; // Will be stored in a Root Component ?
	
public:
	Actor();
	virtual ~Actor(){}

	virtual void Initialize();

	void AddComponent(std::shared_ptr<ComponentBase> Component);
	void RemoveComponent(std::shared_ptr<ComponentBase> Component);
	const std::vector<std::shared_ptr<ComponentBase>>& GetAllComponents() const;
	template<class C>
	std::shared_ptr<C> GetComponentByClass()
	{
		for (std::shared_ptr<ComponentBase> Component : Components)
		{
			if (std::shared_ptr<C> CastedComponent = std::dynamic_pointer_cast<C>(Component))
				return CastedComponent;
		}

		return nullptr;
	}

	const Transform& GetActorTransform() const;
	const Vector3& GetActorLocation() const;
	const Quaternion& GetActorRotation() const;
	const Vector3& GetActorScale() const;

	void SetActorLocation(const Vector3& NewLocation, bool bTriggerEvent = true);
	void AddActorLocation(const Vector3& AddedLocation, bool bTriggerEvent = true);
	void SetActorRotation(const Quaternion& NewRotation, bool bTriggerEvent = true);
	void SetActorScale(const Vector3& NewScale);

	virtual void Update(float DeltaTime);
	virtual void PostUpdate();

	// Event Bindings
	template<class C, void (C::* Function)(const Vector3&)>
	void BindOnLocationSet(C* Instance)
	{
		DelegateBase<void, const Vector3&>* OnLocationSetDelegate = new DelegateBase<void, const Vector3&>();
		OnLocationSetDelegate->Bind<C, Function>(Instance);
		OnLocationSet.push_back(OnLocationSetDelegate);
	}

	template<class C, void (C::* Function)(const Quaternion&)>
	void BindOnRotationSet(C* Instance)
	{
		DelegateBase<void, const Quaternion&>* OnLocationSetDelegate = new DelegateBase<void, const Quaternion&>();
		OnLocationSetDelegate->Bind<C, Function>(Instance);
		OnRotationSet.push_back(OnLocationSetDelegate);
	}

protected:
	//Vector2 ConvertWorldToScreen(const Vector2& WorldCoordinates, const Vector2& ScreenSize);

private:
	// Events
	std::vector<DelegateBase<void, const Vector3&>*> OnLocationSet;
	std::vector<DelegateBase<void, const Quaternion&>*> OnRotationSet;
};

