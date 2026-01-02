#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

#include "../../Helpers/Math/Vectors/Vectors.h"

enum InputTrigger 
{
	PRESSED = 0,
	RELEASED,
	DOWN,
	UP,

};

enum InputType 
{
	KEYBOARD = 0,
	MOUSE_POSITION,
	GAMEPAD
};

struct InputKey 
{
private:
	InputType Type;
	int Value;
	float Scale;
public:
	InputKey(const InputType& InType, const int& InValue, const float& InScale) : Type{ InType }, Value{ InValue }, Scale{ InScale } {}

	const InputType& GetType() const { return Type; }
	const int& GetValue() const { return Value; }
	const float& GetScale() const { return Scale; }
};

struct InputAxis 
{
private:
	InputType Type;
	int Value;
	bool IsAxis;
	Vector2 Scale;
	float DeadZone;

public:
	InputAxis(const InputType& InType, const int& InValue, const bool& InIsAxis, const Vector2& InScale = { 0.0f }, const float& InDeadZone = { 0.0f })
		: Type{ InType }, Value{ InValue }, IsAxis{ InIsAxis }, Scale{ InScale }, DeadZone{ InDeadZone } {}

	const InputType& GetType() const { return Type; }
	const int& GetValue() const { return Value; }
	const bool& GetIsAxis() const { return IsAxis; }
	const Vector2& GetScale() const { return Scale; }
	const float& GetDeadZone() const { return DeadZone; }
};

class InputManager
{
private:
	static std::shared_ptr<InputManager> Instance;

	InputManager(InputManager& InInputManager) = delete;
	void operator=(const InputManager& InInputManager) = delete;

	InputManager();

	bool bIsInGamepadMode = false;

protected:
	std::unordered_map<std::string, std::vector<std::shared_ptr<InputKey>>> EventsBindedInputs;
	std::unordered_map<std::string, std::vector<std::shared_ptr<InputAxis>>> AxisBindedInputs;


	bool IsBindKeyboardInputTriggered(int Input, InputTrigger Trigger) const;
	bool IsBindGamepadInputTriggered(int Input, InputTrigger Trigger) const;
public:
	static std::shared_ptr<InputManager> Get();

	bool IsEventTriggered(std::string EventName, InputTrigger Trigger, int& PressedInput, float& ScaleInput);
	bool IsEventExists(std::string EventName) const;

	bool IsAxisExists(std::string AxisName) const;
	void GetAxisValue(std::string EventName, Vector2& Direction);

	bool GetIsInGamepadMode() const;
};