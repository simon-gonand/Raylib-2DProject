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
    SlideEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, KEY_LEFT_CONTROL, 1.0f));
    SlideEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, 1.0f));
    EventsBindedInputs.insert(std::make_pair(SlideEventName, SlideEventInputs));

    // Grappling Hook Events
    std::string AttractHookEventName = "AttractHook";
    std::vector<std::shared_ptr<InputKey>> AttractHookEventInputs;
    AttractHookEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, MOUSE_BUTTON_RIGHT, 1.0f));
    AttractHookEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_RIGHT_TRIGGER_1, 1.0f));
    EventsBindedInputs.insert(std::make_pair(AttractHookEventName, AttractHookEventInputs));

    std::string BalanceHookEventName = "BalanceHook";
    std::vector<std::shared_ptr<InputKey>> BalanceHookEventInputs;
    BalanceHookEventInputs.push_back(std::make_shared<InputKey>(KEYBOARD, MOUSE_BUTTON_LEFT, 1.0f));
    BalanceHookEventInputs.push_back(std::make_shared<InputKey>(GAMEPAD, GAMEPAD_BUTTON_LEFT_TRIGGER_1, 1.0f));
    EventsBindedInputs.insert(std::make_pair(BalanceHookEventName, BalanceHookEventInputs));

    // --- Axis ---

    // Move Axis
    std::string MoveAxisName = "Move";
    std::vector<std::shared_ptr<InputAxis>> MoveAxisInputs;

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_D, false, Vector::RightVector2));
    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, false, Vector::RightVector2));

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(KEYBOARD, KEY_A, false, Vector::LeftVector2));
    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT, false, Vector::LeftVector2));

    MoveAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_X, true, Vector::RightVector2, 0.5f));

    AxisBindedInputs.insert(std::make_pair(MoveAxisName, MoveAxisInputs));

    // Aim Axis
    std::string AimAxisName = "Aim";
    std::vector<std::shared_ptr<InputAxis>> AimAxisInputs;

    AimAxisInputs.push_back(std::make_shared<InputAxis>(MOUSE_POSITION, -1, true, Vector2({1.0f, 1.0f}))); // Specific exception for MOUSE_POSITION since we only need to get the current Mouse Position

    AimAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_X, true, Vector::RightVector2, 0.5f));
    AimAxisInputs.push_back(std::make_shared<InputAxis>(GAMEPAD, GAMEPAD_AXIS_LEFT_Y, true, Vector::DownVector2, 0.5f));

    AxisBindedInputs.insert(std::make_pair(AimAxisName, AimAxisInputs));
}

std::shared_ptr<InputManager> InputManager::Get()
{
    if(!Instance)
        Instance.reset(new InputManager());

    return Instance;
}

bool InputManager::IsEventTriggered(std::string EventName, InputTrigger Trigger, int& PressedInput, float& ScaleInput)
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
                bIsInGamepadMode = BindedInput->GetType() == GAMEPAD;
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
        return IsKeyReleased(Input) || IsMouseButtonReleased(Input);
    case UP:
        return IsKeyUp(Input) || IsMouseButtonUp(Input);
    case DOWN:
        return IsKeyDown(Input) || IsMouseButtonDown(Input);
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
    bool bMousePositionBinded = false;
    auto BindedInputs = AxisBindedInputs.find(EventName);
    Vector2 GamepadDeadZone = Vector2Zero();
    if (BindedInputs != AxisBindedInputs.end())
    {
        for (std::shared_ptr<InputAxis> BindedInput : BindedInputs->second)
        {
            if (BindedInput->GetIsAxis()) 
            {
                float AxisMovement = 0.0f;
                Vector2 ScaledAxis = Vector2Zero();
                if (BindedInput->GetType() == GAMEPAD)
                {
                    AxisMovement = GetGamepadAxisMovement(0, BindedInput->GetValue());
                    if (BindedInput->GetScale().x > BindedInput->GetScale().y)
                        GamepadDeadZone.x = BindedInput->GetDeadZone();
                    else
                        GamepadDeadZone.y = BindedInput->GetDeadZone();

                    if (!FloatEquals(AxisMovement, 0))
                        bIsInGamepadMode = true;

                    if (!bIsInGamepadMode)
                        continue;

                    ScaledAxis = Vector2Scale(BindedInput->GetScale(), AxisMovement);
                }
                else if (BindedInput->GetType() == MOUSE_POSITION)
                {
                    bMousePositionBinded = true;
                    if (!Vector2Equals(GetMouseDelta(), Vector2Zero()))
                    {
                        bIsInGamepadMode = false;
                    }

                    if (bIsInGamepadMode)
                        continue;
                }
                Direction = Vector2Add(Direction, ScaledAxis);
            }
            else
            {
                if ((BindedInput->GetType() == GAMEPAD && IsGamepadButtonDown(0, BindedInput->GetValue())) || 
                    (BindedInput->GetType() == KEYBOARD && IsKeyDown(BindedInput->GetValue())))
                {
                    bIsInGamepadMode = BindedInput->GetType() == GAMEPAD;
                    Direction = Vector2Add(Direction, BindedInput->GetScale());
                }
            }
        }
    }

    if (bIsInGamepadMode && !Vector2Equals(GamepadDeadZone, Vector2Zero()) && 
        fabs(Direction.x) <= GamepadDeadZone.x && fabs(Direction.y) <= GamepadDeadZone.y)
    {
        Direction = Vector2Zero();
    }
    else if (!bIsInGamepadMode && bMousePositionBinded)
    {
        Direction = GetMousePosition();
    }
    else
    {
        Direction = Vector2Normalize(Direction);
    }
}

bool InputManager::GetIsInGamepadMode() const
{
    return bIsInGamepadMode;
}