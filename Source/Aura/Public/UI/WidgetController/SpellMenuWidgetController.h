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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellGlobeReassignedSignature, const FGameplayTag&, AbilityTag);

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

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature OnSpellPointsChanged;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitingForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;

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

private:	
	static void ShouldEnableButtons(
		const FGameplayTag& AbilityStatus,
		int32 SpellPoints,
		bool& bShouldEnableSpellPointsButton,
		bool& bShouldEnableEquipButton);
	
	void OnAbilityEquipped(
		const FGameplayTag& AbilityTag,
		const FGameplayTag& Status,
		const FGameplayTag& Slot,
		const FGameplayTag& PrevSlot);

	FSelectedAbility SelectedAbility = {
		FAuraGameplayTags::Get().Abilities_None,
		FAuraGameplayTags::Get().Abilities_Status_Locked
	};

	int32 CurrentSpellPoints = 0;
	bool bWaitingForEquipSelection = false;
	FGameplayTag SelectedSlot;
};
