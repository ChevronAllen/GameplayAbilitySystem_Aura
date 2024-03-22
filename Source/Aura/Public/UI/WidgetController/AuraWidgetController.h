// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
protected:
	TObjectPtr<APlayerController> PlayerController;
	TObjectPtr<APlayerState> PlayerState;
	TObjectPtr<UAbilitySystemComponent> AbilistySystemComponent;
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
