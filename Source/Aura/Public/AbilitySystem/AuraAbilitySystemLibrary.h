// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

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
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);
	
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "WorldContextObject"), Category="AuraAbilitySystemLibrary|Widget")
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(
		const UObject* WorldContextObject,
		ECharacterClass CharacterClass,
		float Level,
		UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(
		const UObject* WorldContextObject,
		UAbilitySystemComponent* ASC,
		ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|AbilityInfo")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(
		UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsBlockedHit);

	// UPARAM macros is needed to set a parameter as Input param if param is not const
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(
		UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,
		bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(
		const UObject* WorldContextObject,
		TArray<AActor*>& OutOverlappingActors,
		const TArray<AActor*>& ActorsToIgnore,
		float Radius,
		const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(const AActor* FirstActor, const AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	
	static int32 GetXPRewardForClassAndLevel(
		const UObject* WorldContextObject,
		ECharacterClass CharacterClass,
		int32 CharacterLevel);
};
