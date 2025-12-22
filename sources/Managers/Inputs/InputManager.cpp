#include "InputManager.h"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

std::shared_ptr<InputManager> InputManager::Instance;

InputManager::InputManager()
{
    //TODO Create function to help add and remove inputs / events

    // --- Input Events ---

    // Jump Events
    std::string JumpEventName = "Jump";
    std::vector<std::shared_ptr<InputKey>> JumpEventInputs;
    JumpEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, KEY_SPACE, 1.0f));
    JumpEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN, 1.0f));
    EventsBindedInputs.insert(std::make_pair(JumpEventName, JumpEventInputs));

    // Slide Events
    std::string SlideEventName = "Slide";
    std::vector<std::shared_ptr<InputKey>> SlideEventInputs;
    SlideEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, KEY_LEFT_SHIFT, 1.0f));
    SlideEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, 1.0f));
    EventsBindedInputs.insert(std::make_pair(SlideEventName, SlideEventInputs));

    // Grappling Hook Events
    std::string HookEventName = "Hook";
    std::vector<std::shared_ptr<InputKey>> HookEventInputs;
    HookEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, MOUSE_BUTTON_LEFT, 1.0f));
    HookEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_TRIGGER_1, 1.0f));
    EventsBindedInputs.insert(std::make_pair(HookEventName, HookEventInputs));

    // --- Axis ---

    // Move Axis
    std::string MoveAxisName = "Move";
    std::vector<std::shared_ptr<InputAxis>> MoveAxisInputs;

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_D, false, Vector::RightVector2));
    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, false, Vector::RightVector2));

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_A, false, Vector::LeftVector2));
    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT, false, Vector::LeftVector2));

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_X, true, Vector::RightVector2));
    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_Y, true, Vector::DownVector2)); // Gamepad value are inversed on Y Axis joystick

    AxisBindedInputs.insert(std::make_pair(MoveAxisName, MoveAxisInputs));

    // Aim Axis
    std::string AimAxisName = "Aim";
    std::vector<std::shared_ptr<InputAxis>> AimAxisInputs;

    AimAxisInputs.push_back(std::make_shared<InputAxis>(MOUSE_POSITION, -1, true, Vector2({1.0f, 1.0f}))); // Specific exception for MOUSE_POSITION since we only need to get the current Mouse Position

    AimAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_RIGHT_X, true, Vector::RightVector2));
    AimAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_RIGHT_Y, true, Vector::DownVector2));

    AxisBindedInputs.insert(std::make_pair(AimAxisName, AimAxisInputs));
}

std::shared_ptr<InputManager> InputManager::Get()
{
    if(!Instance)
        Instance.reset(new InputManager());

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
        return IsKeyPressed(Input) || IsMouseButtonPressed(Input);
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

void InputManager::GetAxisValue(std::string EventName, Vector2& Direction)
{
    Direction = Vector2Zero();
    auto BindedInputs = AxisBindedInputs.find(EventName);
    if (BindedInputs != AxisBindedInputs.end())
    {
        for (std::shared_ptr<InputAxis> BindedInput : BindedInputs->second)
        {
            if (BindedInput->GetIsAxis()) 
            {
                float AxisMovement = 0.0f;
                Vector2 ScaledAxis = Vector2One();
                if (BindedInput->GetType() == GAMEPAD)
                {
                    AxisMovement = GetGamepadAxisMovement(0, BindedInput->GetValue()); 
                    ScaledAxis = Vector2Scale(BindedInput->GetScale(), AxisMovement);
                }
                else if (BindedInput->GetType() == MOUSE_POSITION)
                {
                    ScaledAxis = Vector2Subtract(GetMousePosition(), Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});
                    ScaledAxis = Vector2Normalize(ScaledAxis);
                    ScaledAxis = Vector2Multiply(BindedInput->GetScale(), ScaledAxis);
                }
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
