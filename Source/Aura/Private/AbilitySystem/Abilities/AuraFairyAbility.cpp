// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/Abilities/AuraFairyAbility.h"
#include "Character/AuraFairyBase.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AuraAIController.h"

AAuraFairyBase* UAuraFairyAbility::SpawnFairy()
{
	bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return nullptr;

	UWorld* World = GetWorld();
	FTransform Transform = FTransform();//GetAvatarActorFromActorInfo()->GetTransform();
	AActor* Owner = nullptr;
	APawn* Instigator = nullptr;
	ESpawnActorCollisionHandlingMethod CollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAuraFairyBase* FairyActor = World->SpawnActorDeferred< AAuraFairyBase>(FairyActorClass, Transform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	FairyActor->AttachToActor(GetAvatarActorFromActorInfo(), FAttachmentTransformRules::KeepRelativeTransform);
	UGameplayStatics::FinishSpawningActor(FairyActor, Transform);
	
	if (FairyActor->Controller == nullptr)
	{
		FTransform ControllerTransform = FTransform();
		AAuraAIController* FairyController = World->SpawnActorDeferred<AAuraAIController>(FairyActor->AIControllerClass, ControllerTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		UGameplayStatics::FinishSpawningActor(FairyController, ControllerTransform);
		FairyController->Possess(FairyActor);

	}
	
	return FairyActor;
}

void UAuraFairyAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}


