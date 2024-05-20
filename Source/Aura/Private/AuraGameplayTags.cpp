// Copyright Chevron Allen (GameSim)


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),				FString("Increases physical damage"));
	GameplayTags.Attributes_Primary_Intelligence			= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),			FString("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),				FString("Increases armor and armor penetration"));
	GameplayTags.Attributes_Primary_Vigor					= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),					FString("Increases health"));

	GameplayTags.Attributes_Secondary_Armor					= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),					FString("Reduces damage take, improves block chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),		FString(""));
	GameplayTags.Attributes_Secondary_BlockChance			= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),			FString(""));
	GameplayTags.Attributes_Secondary_CriticalHitChance		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),		FString(""));

	GameplayTags.Attributes_Secondary_CriticalHitDamage		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),		FString(""));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString(""));
	GameplayTags.Attributes_Secondary_HealthRegeneration	= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),	FString(""));
	GameplayTags.Attributes_Secondary_ManaRegeneration		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),		FString(""));
	GameplayTags.Attributes_Secondary_MaxHealth				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),				FString(""));
	GameplayTags.Attributes_Secondary_MaxMana				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),				FString(""));

	GameplayTags.Attributes_Vital_Health					= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),					FString(""));
	GameplayTags.Attributes_Vital_Mana						= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),						FString(""));

	// Input Tags

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for Skill 1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for Skill 2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for Skill 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for Skill 4"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag granted when Hit Reacting"));

	/*
	* Abilities
	*/

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("Firebolt Ability Tag"));
	GameplayTags.Abilities_Fairy_Zap = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fairy.Zap"), FString("Fairy Zap Ability Tag"));

	/*
	*	Cooldowns
	*/

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("Firebolt Cooldown Tag"));
	GameplayTags.Cooldown_Fairy_Zap = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fairy.Zap"), FString("FairyZap Cooldown Tag"));
}
