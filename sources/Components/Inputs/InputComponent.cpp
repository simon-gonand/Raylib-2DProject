#include "InputComponent.h"
#include <functional>
#include <iostream>

InputComponent::InputComponent(std::shared_ptr<Actor> InOwner)
	:ComponentBase(InOwner)
{
	// Register in Manager ?
}

void InputComponent::Update(float Tick)
{
	for (std::shared_ptr<InputBinding> BindedInput : BindedInputs)
	{
		int PressedInput;
		float Scale;
		if (InputManager::Get()->IsEventTriggered(BindedInput->GetEventName(), BindedInput->GetTrigger(), PressedInput, Scale)) 
		{
			BindedInput->GetCallback()->Invoke(Scale);
		}
	}

	for (std::shared_ptr<AxisBinding> BindedAxis : BindedAxes)
	{
		if (InputManager::Get()->IsAxisExists(BindedAxis->GetAxisName()))
		{
			MyVector2 Direction = MyVector2::ZeroVector;
			InputManager::Get()->GetAxisValue(BindedAxis->GetAxisName(), Direction);
			BindedAxis->GetCallback()->Invoke(Direction);
		}
	}
}