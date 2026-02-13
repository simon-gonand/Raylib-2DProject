#include "MovementComponentDebugUserWidget.h"

MovementComponentDebugUserWidget::MovementComponentDebugUserWidget(std::shared_ptr<MovementComponent> InMovementComp)
	: TextsWithBackgroundUserWidget("", { "Current Movement Mode : None", "Previous Movement Mode : None" }, true, BLACK, WHITE, Vector2Zero(), 0.0f, Vector2{ 1.0f, 1.0f }, 1.0f, Vector4{2.5f, 2.5f, 2.5f, 2.5f}, Vector4{2.5f, 2.5f, 2.5f, 2.5f}), MovementComp{InMovementComp}
{
}

void MovementComponentDebugUserWidget::Update(float DeltaTime)
{
	TextsWithBackgroundUserWidget::Update(DeltaTime);

	EditTextAtIndex(0, TextFormat("Current Movement Mode : %s", MovementComp->DebugMovementModeStr(MovementComp->GetCurrentMovementMode())));
	EditTextAtIndex(1, TextFormat("Previous Movement Mode : %s", MovementComp->DebugMovementModeStr(MovementComp->GetPreviousMovementMode())));
}

const char* MovementComponentDebugUserWidget::MovementModeToText(EMovementMode MovementMode) const
{
	return nullptr;
}
