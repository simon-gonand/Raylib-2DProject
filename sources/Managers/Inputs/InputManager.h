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
	MyVector2 Scale;

public:
	InputAxis(const InputType& InType, const int& InValue, const bool& InIsAxis, const MyVector2& InScale = { 0.0f, 0.0f })
		: Type{ InType }, Value{ InValue }, IsAxis{ InIsAxis }, Scale { InScale } {}

	const InputType& GetType() const { return Type; }
	const int& GetValue() const { return Value; }
	const bool& GetIsAxis() const { return IsAxis; }
	const MyVector2& GetScale() const { return Scale; }
};

class InputManager
{
protected:
	std::unordered_map<std::string, std::vector<std::shared_ptr<InputKey>>> EventsBindedInputs;
	std::unordered_map<std::string, std::vector<std::shared_ptr<InputAxis>>> AxisBindedInputs;


	bool IsBindKeyboardInputTriggered(int Input, InputTrigger Trigger) const;
	bool IsBindGamepadInputTriggered(int Input, InputTrigger Trigger) const;

	InputManager();

public:
	InputManager(InputManager& InInputManager) = delete;
	void operator=(const InputManager& InInputManager) = delete;

	static std::shared_ptr<InputManager> Get();

	bool IsEventTriggered(std::string EventName, InputTrigger Trigger, int& PressedInput, float& ScaleInput) const;
	bool IsEventExists(std::string EventName) const;

	bool IsAxisExists(std::string AxisName) const;
	void GetAxisValue(std::string EventName, MyVector2& Direction) const;
};