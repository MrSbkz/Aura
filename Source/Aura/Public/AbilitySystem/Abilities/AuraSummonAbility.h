// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category="Summonning")
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, Category="Summonning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category="Summonning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category="Summonning")
	float MinSpawnDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category="Summonning")
	float MaxSpawnDistance = 400.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Summonning")
	float SpawnSpread = 90.f;

};
