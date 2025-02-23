// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * Add the following to the Config/DefaultGame.ini file:
	[/Script/GameplayAbilities.AbilitySystemGlobals]
	+AbilitySystemGlobalsClassName="/Script/Aura.AuraAbilitySystemGlobals"
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
