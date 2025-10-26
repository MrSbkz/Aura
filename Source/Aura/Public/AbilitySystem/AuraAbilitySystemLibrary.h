// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class ULoadScreenSaveGame;
class UAbilityInfo;
class AAuraHUD;
struct FWidgetControllerParams;
class USpellMenuWidgetController;
struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Widget Controller
	 */
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams,
	                                       AAuraHUD*& OutAuraHUD);

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);


	/**
	 * Ability System Class Defaults
	 */
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(
		const UObject* WorldContextObject,
		ECharacterClass CharacterClass,
		float Level,
		UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributesFromSaveData(
		const UObject* WorldContextObject,
		UAbilitySystemComponent* ASC,
		ULoadScreenSaveGame* SaveGame);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(
		const UObject* WorldContextObject,
		UAbilitySystemComponent* ASC,
		ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|AbilityInfo")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	
	/**
	 * Effect Context Getters
	 */

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetKnockbackForceMagnitude(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle);


	/**
	 * Effect Context Setters
	 */
	
	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsBlockedHit);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsCriticalHit);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsSuccessfulDebuff(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsSuccessfulDebuff);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDamage(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InDebuffDamage);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDuration(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InDebuffDuration);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffFrequency(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InDebuffFrequency);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDamageType(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FGameplayTag& InDamageType);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDeathImpulse(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InDeathImpulse);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetKnockbackForceMagnitude(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InKnockbackForceMagnitude);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetKnockbackForce(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InKnockbackForce);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsRadialDamage(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsRadialDamage);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetRadialDamageInnerRadius(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InRadialDamageInnerRadius);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetRadialDamageOuterRadius(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		float InRadialDamageOuterRadius);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetRadialDamageOrigin(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InRadialDamageOrigin);

	/**
	 * Gameplay Mechanics
	 */

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(
		const UObject* WorldContextObject,
		TArray<AActor*>& OutOverlappingActors,
		const TArray<AActor*>& ActorsToIgnore,
		float Radius,
		const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(const AActor* FirstActor, const AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetClosestTargets(
		int32 MaxTargets,
		const TArray<AActor*>& Actors,
		const FVector& Origin,
		TArray<AActor*>& OutClosestTargets);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotators(
		const FVector& Forward,
		const FVector& Axis,
		float Spread,
		int32 NumRotators);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlyRotatedVectors(
		const FVector& Forward,
		const FVector& Axis,
		const float Spread,
		int32 NumVectors);

	static int32 GetXPRewardForClassAndLevel(
		const UObject* WorldContextObject,
		ECharacterClass CharacterClass,
		int32 CharacterLevel);

	/*
	 * Damage Effect Params
	 */

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetIsRadialDamageEffectParam(
		UPARAM(ref) FDamageEffectParams& DamageEffectParams,
		bool bIsRadial,
		float InnerRadius,
		float OuterRadius,
		FVector Origin);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetKnockbackDirection(
		UPARAM(ref) FDamageEffectParams& DamageEffectParams,
		FVector KnockbackDirection,
		float Magnitude = 0.f);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetDeathImpulseDirection(
		UPARAM(ref) FDamageEffectParams& DamageEffectParams,
		FVector ImpulseDirection,
		float Magnitude = 0.f);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetTargetEffectParamsASC(
		UPARAM(ref) FDamageEffectParams& DamageEffectParams,
		UAbilitySystemComponent* InASC);
};
