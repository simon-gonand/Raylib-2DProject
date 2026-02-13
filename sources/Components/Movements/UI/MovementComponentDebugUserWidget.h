#pragma once

#include "../../../UI/UserWidgets/Custom/TextsWithBackground/TextsWithBackgroundUserWidget.h"
#include "../MovementComponent.h"

class MovementComponentDebugUserWidget : public TextsWithBackgroundUserWidget
{
public:
	MovementComponentDebugUserWidget(std::shared_ptr<MovementComponent> InMovementComp);

private:
	std::shared_ptr<MovementComponent> MovementComp;

	void Update(float DeltaTime) override;
	const char* MovementModeToText(EMovementMode MovementMode) const;
};