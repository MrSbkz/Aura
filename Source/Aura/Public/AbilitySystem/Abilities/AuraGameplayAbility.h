// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level);
	virtual FString GetNextLevelDescription(int32 Level);
	static FString GetLockedDescription(int32 Level);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

protected:
	float GetManaCost(float InLevel = 1.f) const;
	float GetCooldown(float InLevel = 1.f) const;
};
