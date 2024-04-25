// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/Abilities/AuraFairyAbility.h"
#include "Character/AuraFairyBase.h"
#include "Kismet/GameplayStatics.h"

AAuraFairyBase* UAuraFairyAbility::SpawnFairy()
{
	bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return nullptr;

	UWorld* World = GetWorld();
	FTransform Transform = GetAvatarActorFromActorInfo()->GetTransform();
	AActor* Owner = nullptr;
	APawn* Instigator = nullptr;
	ESpawnActorCollisionHandlingMethod CollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAuraFairyBase* FairyActor = World->SpawnActorDeferred< AAuraFairyBase>(FairyActorClass, Transform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	UGameplayStatics::FinishSpawningActor(FairyActor, Transform);

	return FairyActor;
}

void UAuraFairyAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}


