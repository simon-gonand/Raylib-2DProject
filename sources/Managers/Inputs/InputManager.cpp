#include "InputManager.h"

#include <raylib.h>
#include <raymath.h>

std::shared_ptr<InputManager> InputManager::Instance;

InputManager::InputManager()
{
    //TODO Create function to help add and remove inputs / events
    std::string EventName = "Jump";
    std::vector<std::shared_ptr<InputKey>> EventInputs;
    EventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, KEY_SPACE, 1.0f));
    EventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN, 1.0f));
    EventsBindedInputs.insert(std::make_pair(EventName, EventInputs));

    std::string AxisName = "Move";
    std::vector<std::shared_ptr<InputAxis>> AxisInputs;

    AxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_D, false, Vector::RightVector2));
    AxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, false, Vector::RightVector2));

    AxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_A, false, Vector::LeftVector2));
    AxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT, false, Vector::LeftVector2));

    AxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_X, true, Vector::RightVector2));
    AxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_Y, true, Vector::DownVector2)); // Gamepad value are inversed on Y Axis joystick

    AxisBindedInputs.insert(std::make_pair(AxisName, AxisInputs));
}

std::shared_ptr<InputManager> InputManager::Get()
{
    if(!Instance)
        Instance = std::make_shared<InputManager>();

    return Instance;
}

bool InputManager::IsEventTriggered(std::string EventName, InputTrigger Trigger, int& PressedInput, float& ScaleInput) const
{
    auto BindedInputs = EventsBindedInputs.find(EventName);
    if (BindedInputs != EventsBindedInputs.end())
    {
        for (std::shared_ptr<InputKey> BindedInput : BindedInputs->second)
        {
            if ((BindedInput->GetType() == KEYBOARD && IsBindKeyboardInputTriggered(BindedInput->GetValue(), Trigger)) ||
                (BindedInput->GetType() == GAMEPAD && IsBindGamepadInputTriggered(BindedInput->GetValue(), Trigger))) 
            {
                PressedInput = BindedInput->GetValue();
                ScaleInput = BindedInput->GetScale();
                return true;
            }
        }
    }

    return false;
}

bool InputManager::IsBindKeyboardInputTriggered(int Input, InputTrigger Trigger) const
{
    switch (Trigger)
    {
    case PRESSED:
        return IsKeyPressed(Input);
    case RELEASED:
        return IsKeyReleased(Input);
    case UP:
        return IsKeyUp(Input);
    case DOWN:
        return IsKeyDown(Input);
    }
    return false;
}

bool InputManager::IsBindGamepadInputTriggered(int Input, InputTrigger Trigger) const
{
    switch (Trigger)
    {
    case PRESSED:
        return IsGamepadButtonPressed(0, Input);
    case RELEASED:
        return IsGamepadButtonReleased(0, Input);
    case UP:
        return IsGamepadButtonUp(0, Input);
    case DOWN:
        return IsGamepadButtonDown(0, Input);
    }
    return false;
}

bool InputManager::IsEventExists(std::string EventName) const
{
    return EventsBindedInputs.find(EventName) != EventsBindedInputs.end();
        
}

bool InputManager::IsAxisExists(std::string EventName) const
{
    return AxisBindedInputs.find(EventName) != AxisBindedInputs.end();;
}

void InputManager::GetAxisValue(std::string EventName, Vector2& Direction) const
{
    Direction = Vector2Zero();
    auto BindedInputs = AxisBindedInputs.find(EventName);
    if (BindedInputs != AxisBindedInputs.end())
    {
        for (std::shared_ptr<InputAxis> BindedInput : BindedInputs->second)
        {
            if (BindedInput->GetIsAxis()) 
            {
                float AxisMovement = GetGamepadAxisMovement(0, BindedInput->GetValue());
                Vector2 ScaledAxis = Vector2Scale(BindedInput->GetScale(), AxisMovement);
                Direction = Vector2Add(Direction, ScaledAxis);
            }
            else
            {
                if ((BindedInput->GetType() == GAMEPAD && IsGamepadButtonDown(0, BindedInput->GetValue())) || 
                    (BindedInput->GetType() == KEYBOARD && IsKeyDown(BindedInput->GetValue())))
                {
                    Direction = Vector2Add(Direction, BindedInput->GetScale());
                }
            }
        }
    }

    Direction = Vector2Normalize(Direction);
}
