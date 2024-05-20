// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/Data/AbilityInfo.h"


FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag AbilityTag, bool bLogNotFound) const
{
   

    for (const FAuraAbilityInfo AbilityInfo : AbilityInformation)
    {
        if (AbilityInfo.AbilityTag.MatchesTagExact(AbilityTag)) 
        {
            return AbilityInfo;
        }
    }
    if (bLogNotFound) 
    {
        UE_LOG(LogTemp, Display, TEXT("Could not find info for AbilityTag [%s] on AbilityInfo [%s]"),*AbilityTag.ToString(),*GetNameSafe(this));
    }

    return FAuraAbilityInfo();
}
