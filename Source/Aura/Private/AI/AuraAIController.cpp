// Copyright Chevron Allen (GameSim)


#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAuraAIController::AAuraAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	check(AIPerceptionComponent);

}

EAIAwarenessState AAuraAIController::GetAwarenessState()
{
	return AwarenessState;
}

void AAuraAIController::AddObservedActor(AActor* Actor)
{
	check(Actor);
	AwarenessTarget = Actor;
	AwarenessState = EAIAwarenessState::FullyAware;
	Blackboard->SetValueAsEnum(AwarenessStateKey, EAIAwarenessState::FullyAware);
	float Distance = FVector::Distance(GetPawn()->GetActorLocation(), Actor->GetActorLocation());
	UObject* BlackBoardStoredObject = Blackboard->GetValueAsObject(PlayerCharacterKey);
	if (AwarenessTarget != BlackBoardStoredObject && AwarenessTarget != nullptr)
	{
		Blackboard->SetValueAsObject(PlayerCharacterKey, AwarenessTarget);
		Blackboard->SetValueAsFloat(TargetDistanceKey, Distance);
	}
}

void AAuraAIController::RemovedObservedActor()
{
	AwarenessTarget = nullptr;
	AwarenessState = EAIAwarenessState::None;
	Blackboard->SetValueAsEnum(AwarenessStateKey, EAIAwarenessState::None);
	Blackboard->SetValueAsObject(PlayerCharacterKey, AwarenessTarget);
}

float AAuraAIController::IncreaseAwareness_Implementation(AActor* PercievedActor)
{
	if (PercievedActor == nullptr)
		return PerceptionAwareness;

	float OldAwareness = PerceptionAwareness;
	float NewAwareness = OldAwareness + AwarenessIncreaseSpeed;
	bool TriggerEventDelegate = false;

	if (OldAwareness < PerceptionAwarenessThreshold && NewAwareness >= PerceptionAwarenessThreshold)
	{
		TriggerEventDelegate = true;
	}


	NewAwareness = FMath::Min(NewAwareness, PerceptionAwarenessThreshold*1.5f);
	PerceptionAwareness = NewAwareness;
	if (TriggerEventDelegate)
	{
		AddObservedActor(PercievedActor);
		OnAwarenessGained.Broadcast(PercievedActor);
	}
	return PerceptionAwareness;
}

float AAuraAIController::DecreaseAwareness_Implementation()
{
	float OldAwareness = PerceptionAwareness;
	float NewAwareness = OldAwareness - AwarenessDecreaseSpeed;
	bool TriggerEventDelegate = false;

	if (OldAwareness > 0 && NewAwareness <= 0)
	{
		TriggerEventDelegate = true;
	}
	if (OldAwareness >= PerceptionAwarenessThreshold && NewAwareness < PerceptionAwarenessThreshold)
	{
		AwarenessState = EAIAwarenessState::LosingAwareness;
		Blackboard->SetValueAsEnum(AwarenessStateKey, EAIAwarenessState::LosingAwareness);
	}

	NewAwareness = FMath::Max(NewAwareness, 0);
	PerceptionAwareness = NewAwareness;
	if (TriggerEventDelegate)
	{
		RemovedObservedActor();
		OnAwarenessLost.Broadcast();
	}
	return PerceptionAwareness;
}

void AAuraAIController::ResetAwareness_Implementation()
{
	PerceptionAwareness = 0;
}

