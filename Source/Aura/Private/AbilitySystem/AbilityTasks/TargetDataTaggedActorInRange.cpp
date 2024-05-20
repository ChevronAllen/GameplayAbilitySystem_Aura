// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/AbilityTasks/TargetDataTaggedActorInRange.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"

UTargetDataTaggedActorInRange* UTargetDataTaggedActorInRange::CreateTargetDataTaggedActorInRange(UGameplayAbility* OwningAbility, FName Tag, float MaxRange)
{
	UTargetDataTaggedActorInRange* MyObj = NewAbilityTask<UTargetDataTaggedActorInRange>(OwningAbility);
	MyObj->TagToFind = Tag;
	MyObj->MaxRange = MaxRange;

	return MyObj;
}

void UTargetDataTaggedActorInRange::Activate()
{
	Super::Activate();
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		FindNearestActor();
		SendActorData(TagToFind);
	}
	else
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataTaggedActorInRange::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataTaggedActorInRange::SendActorData(FName Tag)
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	TArray< TWeakObjectPtr<AActor> > OutputData;
	OutputData.Add(TWeakObjectPtr<AActor>(NearestActor));

	FGameplayAbilityTargetData_ActorArray* Data = new FGameplayAbilityTargetData_ActorArray();
	Data->SetActors(OutputData);

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

AActor* UTargetDataTaggedActorInRange::FindNearestActor()
{
	TArray<AActor*> TargetActors = TArray<AActor*>();
	NearestActor = nullptr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagToFind, TargetActors);
	if (TargetActors.Num() > 0)
	{
		AActor* OwnerAvatar = GetAvatarActor();
		float shortestDistance = OwnerAvatar->GetDistanceTo(TargetActors[0]);

		for (AActor* Actor : TargetActors)
		{
			float distance = OwnerAvatar->GetDistanceTo(Actor);
			if (distance > MaxRange)
				continue;

			if (distance <= shortestDistance)
			{
				shortestDistance = distance;
				NearestActor = Actor;
			}
		}
	}
	return NearestActor;
}

void UTargetDataTaggedActorInRange::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
