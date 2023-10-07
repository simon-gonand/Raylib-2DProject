#pragma once

#include <string>
#include <functional>
#include <raylib.h>

#include "../BaseClass/ComponentBase.h"
#include "../../Managers/Inputs/InputManager.h"
#include "../../Utils/Delegates/DelegateBase/DelegateBase.h"

struct InputBinding 
{
private:
	const std::string EventName;
	DelegateBase<void, const float&>* Callback;
	const InputTrigger Trigger;

public:
	InputBinding(const std::string& InEventName, DelegateBase<void, const float&>* InCallback, const InputTrigger& InTrigger)
		: EventName{ InEventName }, Callback{ InCallback }, Trigger{ InTrigger } {}

	InputBinding(InputBinding& CopyRef) = delete;
	InputBinding(InputBinding&& MoveRef) = delete;
	int operator =(InputBinding& AssignmentRef) = delete;

	const std::string& GetEventName() const { return EventName; }
	const InputTrigger& GetTrigger() const { return Trigger; }
	DelegateBase<void, const float&>* GetCallback() const { return Callback; }
};

struct AxisBinding
{
private:
	const std::string AxisName;
	DelegateBase<void, const MyVector2&>* Callback;
	
public:
	AxisBinding(const std::string& InAxisName, DelegateBase<void, const MyVector2&>* InCallback) : AxisName { InAxisName }, Callback { InCallback } {}

	AxisBinding(AxisBinding& CopyRef) = delete;
	AxisBinding(AxisBinding&& MoveRef) = delete;
	int operator =(AxisBinding& AssignmentRef) = delete;

	const std::string& GetAxisName() const { return AxisName; }
	DelegateBase<void, const MyVector2&>* GetCallback() const { return Callback; }
};

class InputComponent: public ComponentBase
{
private:
	std::vector<std::shared_ptr<InputBinding>> BindedInputs;
	std::vector <std::shared_ptr<AxisBinding>> BindedAxes;

public:
	InputComponent(std::shared_ptr<Actor> InOwner);

	template<class C, void (C::* Function)(const float&)>
	void BindInput(const std::string& EventName, const InputTrigger& Trigger, C* Instance)
	{
		DelegateBase<void, const float&>* InputDelegate = new DelegateBase<void, const float&>();
		InputDelegate->Bind<C, Function>(Instance);
		if (InputManager::Get()->IsEventExists(EventName))
		{
			BindedInputs.push_back(std::make_shared<InputBinding>(EventName, InputDelegate, Trigger));
		}
	}

	template<class C, void (C::* Function)(const MyVector2&)>
	void BindAxis(const std::string& AxisName, C* Instance) 
	{
		DelegateBase<void, const MyVector2&>* AxisDelegate = new DelegateBase<void, const MyVector2&>();
		AxisDelegate->Bind<C, Function>(Instance);
		if (InputManager::Get()->IsAxisExists(AxisName)) 
		{
			BindedAxes.push_back(std::make_shared<AxisBinding>(AxisName, AxisDelegate));
		}
	}

	// From ComponentBase
	virtual void Update(float Tick) override;
};

