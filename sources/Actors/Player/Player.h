#pragma once

#include "../BaseClass/Actor.h"

class Player: public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Draw() override;

	void Move(const Vector2& Scale);
	void Jump(const float& Scale);

	std::shared_ptr<class InputComponent> InputComp;
	std::shared_ptr<class PhysicsComponent> PhysicsComp;
};

