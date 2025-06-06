// Copyright PK

#include "Input/AuraInputConfig.h"
#include "Aura/AuraLogChannels.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(
	const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find AbilityInputAction for InputTag: [%s], on InputConfig [%s]"),
		       *InputTag.ToString(),
		       *GetNameSafe(this));
	}

	return nullptr;
}
