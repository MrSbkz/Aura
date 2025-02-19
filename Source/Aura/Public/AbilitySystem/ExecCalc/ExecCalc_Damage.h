// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


private:
	static void CalculateAttributeMagnitude(
		const FGameplayEffectCustomExecutionParameters&,
		const FGameplayEffectAttributeCaptureDefinition& Attribute,
		const FAggregatorEvaluateParameters& EvaluateParameters,
		float& Value);
};
