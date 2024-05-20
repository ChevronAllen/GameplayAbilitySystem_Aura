// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataTaggedActorInRange.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataTaggedActorInRange : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "AbilityTasks", meta = (DisplayName = "Target Data Tagged Actor In Range", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UTargetDataTaggedActorInRange* CreateTargetDataTaggedActorInRange(UGameplayAbility* OwningAbility,FName Tag,float MaxRange = 500.0f);

	UPROPERTY(BlueprintAssignable)
	FActorTargetDataSignature ValidData;

private:
	FName TagToFind;
	float MaxRange;
	AActor* NearestActor = nullptr;

	virtual void Activate() override;
	void SendActorData(FName Tag);
	AActor* FindNearestActor();

	UFUNCTION()
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
