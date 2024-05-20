// Copyright Chevron Allen (GameSim)


#include "Character/AuraFairyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraFairyBase::AAuraFairyBase()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

}

void AAuraFairyBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilityClass) 
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1.0f);
		AutoAbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AAuraFairyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	if (AuraAIController = Cast<AAuraAIController>(NewController))
	{
		AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AuraAIController->RunBehaviorTree(BehaviorTree);
	}
}