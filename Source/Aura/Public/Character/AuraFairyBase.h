// Copyright Chevron Allen (GameSim)

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraEnemy.h"
#include "AuraFairyBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraFairyBase : public AAuraEnemy
{
	GENERATED_BODY()

public:
	AAuraFairyBase();

protected:
	FGameplayAbilitySpecHandle CurrentAbilitySpecHandle;
};
