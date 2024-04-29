// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/AutomaticGameplayAbility.h"
#include "AuraFairyBase.generated.h"

class UAuraAbilitySystemComponent;
class UAutomaticGameplayAbility;
class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraFairyBase : public ACharacter 
{
	GENERATED_BODY()

public:
	AAuraFairyBase(); 
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	FGameplayAbilitySpecHandle CurrentAbilitySpecHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr <AAuraAIController> AuraAIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fairy")
	TSubclassOf <UAutomaticGameplayAbility> AbilityClass;
};
