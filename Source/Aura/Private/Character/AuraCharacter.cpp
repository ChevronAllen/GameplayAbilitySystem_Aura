// Copyright Chevron Allen (GameSim)


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"	
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init AbilityActorInfo for the server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init AbilityActorInfo for the client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AController* CharacterController = GetController();
	AAuraPlayerState* AuraPlayerState = nullptr;
	if (CharacterController)
	{
		AuraPlayerState = CharacterController->GetPlayerState<AAuraPlayerState>();
		check(AuraPlayerState);
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
		Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();
	}

	// Test for null. The client wont have a controller for all players
	if (AAuraPlayerController* AuraPlayercontroller = Cast<AAuraPlayerController>(CharacterController))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayercontroller->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayercontroller, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
		
	}
}
