// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraFairyAbility.generated.h"
class AAuraCharacterBase;
class AAuraFairyBase;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFairyAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AAuraFairyBase> FairyActorClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AAuraFairyBase> FairyActorInstance;

	UFUNCTION(BlueprintCallable)
	AAuraFairyBase* SpawnFairy();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
