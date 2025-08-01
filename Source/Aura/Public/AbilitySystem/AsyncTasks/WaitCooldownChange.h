// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChange.generated.h"

struct FGameplayEffectSpec;
class UAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChangeSignature, float, TimeRemaining);


/**
 * UWaitCooldownChange is a blueprint async action class used to wait for cooldown changes
 * associated with a specific GameplayTag on an Ability System Component (ASC).
 * It enables event-driven gameplay behavior by broadcasting events when a cooldown starts or ends.
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy="AsyncTask"))
class AURA_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEnd;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UWaitCooldownChange* WaitForCooldownChange(
		UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayTag& InCooldownTag
	);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;

	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);
	void OnActiveEffectAdded(
		UAbilitySystemComponent* TargetASC,
		const FGameplayEffectSpec& SpecApplied,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
