// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AutomaticGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAutomaticGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnBlackboardEvent(const FGameplayEventData& EventData);
};
