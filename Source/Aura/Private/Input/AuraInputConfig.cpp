// Copyright Chevron Allen (GameSim)


#include "Input/AuraInputConfig.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityinputActionForTag(const FGameplayTag& Tag, bool bLogNotFound)
{
    for (const FAuraInputAction AuraAction : AbilityInputActions)
    {
        if (AuraAction.InputAction && Tag.MatchesTagExact(AuraAction.InputTag))
        {
            return AuraAction.InputAction;
        }
    }

    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find Input action for Tag [%s]"), *Tag.ToString());
    }

    return nullptr;
}
