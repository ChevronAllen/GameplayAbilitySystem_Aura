// Copyright Chevron Allen (GameSim)


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue); } );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnManaChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}

		AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		

		AuraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer AssetTags)
			{
				for (auto const Tag : AssetTags)
				{
					const FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message")); 
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						if(Row != nullptr)
							MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}

 }

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraASC)
{
	//TODO Get information about all given abilitie, look up their ability info and broadcast it to widgets
	if (!AuraASC->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	TArray<FAuraAbilityInfo> AbilityInfoList;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec) 
	{
		FGameplayTag AbilityTag = UAuraAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec);
		FGameplayTag InputTag = UAuraAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
		Info.InputTag = InputTag;

		AbilityInfoDelegate.Broadcast(Info);
	});
	AuraASC->ForEachAbility(BroadcastDelegate);
}
