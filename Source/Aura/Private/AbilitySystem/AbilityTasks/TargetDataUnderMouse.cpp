// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);



	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	if (APlayerController* Controller = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult CursorHit;
		Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
		ValidData.Broadcast(CursorHit.Location);
	}
}
