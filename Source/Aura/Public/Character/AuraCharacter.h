// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	/** CombatInterface **/
	virtual int32 GetPlayerLevel() const override;
	/**  end CombatInterface **/

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
protected:
	virtual void InitAbilityActorInfo() override;

};
