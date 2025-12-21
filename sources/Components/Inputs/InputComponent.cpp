#include "InputComponent.h"
#include <functional>
#include <iostream>
#include <raymath.h>

InputComponent::InputComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate)
	:ComponentBase(InOwner, bAutoActivate)
{
}

void InputComponent::Update(float DeltaTime)
{
	for (std::shared_ptr<InputBinding> BindedInput : BindedInputs)
	{
		int PressedInput;
		float Scale;
		if (InputManager::Get()->IsEventTriggered(BindedInput->GetEventName(), BindedInput->GetTrigger(), PressedInput, Scale)) 
		{
			BindedInput->GetCallback()->Invoke(Scale, BindedInput->GetTrigger());
		}
	}

	for (std::shared_ptr<AxisBinding> BindedAxis : BindedAxes)
	{
		if (InputManager::Get()->IsAxisExists(BindedAxis->GetAxisName()))
		{
			Vector2 Direction = Vector2Zero();
			InputManager::Get()->GetAxisValue(BindedAxis->GetAxisName(), Direction);
			BindedAxis->GetCallback()->Invoke(Direction);
		}
	}
}