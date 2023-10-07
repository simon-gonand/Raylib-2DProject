#pragma once

#include "../BaseClass/Actor.h"
#include "../../Helpers/Math/Vectors/Vectors.h"

class Player: public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Draw() override;

	void Move(const MyVector2& Scale);
	void Jump(const float& Scale);

	std::shared_ptr<class InputComponent> InputComp;
};

