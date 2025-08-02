// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FSpellGlobeSelectedSignature,
	bool, bSpellPointsButtonEnabled,
	bool, bEquipButtonEnabled,
	FString, Description,
	FString, NextLevelDescription);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag&, AbilityType);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnPlayerStatChangedSignature OnSpellPointsChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FWaitForEquipSelectionSignature StopWaitingForEquipDelegate;

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void GlobeDeselect();

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag/*InputTag*/, const FGameplayTag& AbilityType);	

	
	void OnAbilityEquipped(
		const FGameplayTag& AbilityTag,
		const FGameplayTag& Status,
		const FGameplayTag& Slot,
		const FGameplayTag& PrevSlot);
private:	
	static void ShouldEnableButtons(
		const FGameplayTag& AbilityStatus,
		int32 SpellPoints,
		bool& bShouldEnableSpellPointsButton,
		bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility = {
		FAuraGameplayTags::Get().Abilities_None,
		FAuraGameplayTags::Get().Abilities_Status_Locked
	};

	int32 CurrentSpellPoints = 0;
	bool bWaitingForEquipSelection = false;
	FGameplayTag SelectedSlot;
};
