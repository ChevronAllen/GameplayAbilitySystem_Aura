// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interaction/BehaviorInterface.h"
#include "AuraAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAwareDelegate, class AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAwarenessLostDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAwarenessStateChanged, EAIAwarenessState, NewState);

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraAIController : public AAIController, public IBehaviorInterface
{
	GENERATED_BODY()
	
public:
	AAuraAIController();
	UPROPERTY(BlueprintAssignable)
	FOnAwareDelegate OnAwarenessGained;
	UPROPERTY(BlueprintAssignable)
	FOnAwarenessLostDelegate OnAwarenessLost;
	
	
	

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EAIAwarenessState> AwarenessState;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AActor> AwarenessTarget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector AwarenessTargetPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PerceptionAwareness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AwarenessIncreaseSpeed = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AwarenessDecreaseSpeed = 2.0f;
	UFUNCTION( BlueprintCallable,BlueprintPure)
	EAIAwarenessState GetAwarenessState();

	UPROPERTY(BlueprintReadOnly)
	float PerceptionAwarenessThreshold = 100;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float IncreaseAwareness(AActor* PercievedActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float DecreaseAwareness();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetAwareness();
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName PlayerCharacterKey= "PlayerCharacter";
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName TargetDistanceKey	= "DistanceToPlayer";
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName TargetLocationKey	= "TargetActorLocation";
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName AwarenessStateKey = "AwarenessState";

private:

	void AddObservedActor(AActor* Actor);
	void RemovedObservedActor();
};
