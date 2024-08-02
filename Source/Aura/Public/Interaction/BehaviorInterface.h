// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BehaviorInterface.generated.h"


UENUM(BlueprintType, meta = (ScriptName = "AIAwarenessState"))
enum EAIAwarenessState {
	None,
	LosingAwareness,
	FullyAware
};
UENUM(BlueprintType,meta=(ScriptName="AIBehaviorState"))
enum EAIBehaviorState {
	Idle, 
	Search,
	Investigate,
	Attack
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IBehaviorInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	float GetDesiredAttackRange();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetInvestigationRange();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool TryActivateAttack();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	AActor* GetTargetActor();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAIBehaviorState GetBehaviourState();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetBehaviourState(EAIBehaviorState State);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float IncreaseAwareness(AActor* PercievedActor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float DecreaseAwareness();

};
