// Copyright PK

#pragma once

#include "CoreMinimal.h"

/**
 * AuraGameplay Tags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

private:
	static FAuraGameplayTags GameplayTags;
};
