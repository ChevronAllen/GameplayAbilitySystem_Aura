// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraFairyAbility.generated.h"
class AAuraCharacterBase;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFairyAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AAuraCharacterBase> FairyActorClass;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AAuraCharacterBase> FairyActorInstance;
};
