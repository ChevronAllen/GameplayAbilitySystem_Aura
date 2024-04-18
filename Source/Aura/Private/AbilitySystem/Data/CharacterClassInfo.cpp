// Copyright Chevron Allen (GameSim)


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
    return CharacterClassInformation.FindChecked(CharacterClass);
}
