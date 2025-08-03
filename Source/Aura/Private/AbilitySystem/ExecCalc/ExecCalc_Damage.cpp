// Copyright PK


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightingResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	AuraDamageStatics()
	{
		/*
		 * Params:
		 * ClassType, PropertyName(e.g. ArmorProperty - FGameplayAttribute),
		 * EGameplayEffectAttributeCaptureSource(Source or target), bSnapshot
		*/
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightingResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightingResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, DamageStatics().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lighting, DamageStatics().LightingResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, DamageStatics().PhysicalResistanceDef);

	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// Debuff
	DetermineDebuff(ExecutionParams, Spec, EvaluateParameters, TagsToCaptureDefs);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceTag),
		       TEXT("TagsToCaptureDefs doesn't contain Tag: [%s]"), *ResistanceTag.ToString());

		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		Damage += DamageTypeValue;
	}

	// Capture BlockChance on Target, and determine if there was a successful Block
	float TargetBlockChance = 0.f;
	CalculateAttributeMagnitude(ExecutionParams, DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	// If Block, halve the damage
	Damage = bBlocked ? Damage / 2.f : Damage;

	float TargetArmor = 0.f;
	CalculateAttributeMagnitude(ExecutionParams, DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);

	float SourceArmorPenetration = 0.f;
	CalculateAttributeMagnitude(
		ExecutionParams,
		DamageStatics().ArmorPenetrationDef,
		EvaluateParameters,
		SourceArmorPenetration);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

	// ArmorPenetration ignores a percent of the Target's Armor
	const float EffectiveArmor = TargetArmor * (100.f - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;
	// Armor ignores a percentage of incoming Damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	float SourceCriticalHitChance = 0.f;
	CalculateAttributeMagnitude(
		ExecutionParams,
		DamageStatics().CriticalHitChanceDef,
		EvaluateParameters,
		SourceCriticalHitChance);

	float TargetCriticalHitResistance = 0.f;
	CalculateAttributeMagnitude(
		ExecutionParams,
		DamageStatics().CriticalHitResistanceDef,
		EvaluateParameters,
		TargetCriticalHitResistance);

	float SourceCriticalHitDamage = 0.f;
	CalculateAttributeMagnitude(
		ExecutionParams,
		DamageStatics().CriticalHitDamageDef,
		EvaluateParameters,
		SourceCriticalHitDamage);


	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(
		TargetPlayerLevel);

	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance *
		CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	// Double damage plus a bonus if critical hit
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(
		UAuraAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive,
		Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UExecCalc_Damage::DetermineDebuff(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters,
	const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& TagsToCaptureDefs) const
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	for (const TPair<FGameplayTag, FGameplayTag>& Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > -0.5f) // 0.5 padding for floating points [im]precision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistance[DamageType];
			CalculateAttributeMagnitude(
				ExecutionParams,
				TagsToCaptureDefs[ResistanceTag],
				EvaluateParameters,
				TargetDebuffResistance);

			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			if (const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance)
			{
				FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(EffectContextHandle, bDebuff);
				UAuraAbilitySystemLibrary::SetDamageType(EffectContextHandle, DamageType);

				const float DebuffDDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false);
				UAuraAbilitySystemLibrary::SetDebuffDamage(EffectContextHandle, DebuffDDamage);

				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false);
				UAuraAbilitySystemLibrary::SetDebuffDuration(EffectContextHandle, DebuffDuration);

				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(EffectContextHandle, DebuffFrequency);
			}
		}
	}
}

void UExecCalc_Damage::CalculateAttributeMagnitude(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FGameplayEffectAttributeCaptureDefinition& Attribute,
	const FAggregatorEvaluateParameters& EvaluateParameters,
	float& Value)
{
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		Attribute,
		EvaluateParameters,
		Value);
	Value = FMath::Max<float>(Value, 0.f);
}
