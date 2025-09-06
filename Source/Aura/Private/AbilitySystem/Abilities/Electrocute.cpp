// Copyright PK


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>ELECTROCUTE</>\n\n"
				"<Small>Level: </><Level>%d</>\n"
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				"<Default>Emits a beam of lighting connecting with target, repeatedly causing "
				"</><Damage>%d</><Default> lighting damage with a chance to stun</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage
		);
	}

	return FString::Printf(
		TEXT("<Title>ELECTROCUTE</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Emits %d beams of lighting connecting with targets, repeatedly causing "
			"</><Damage>%d</><Default> Lighting damage with a chance to stun</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShockTargets),
		ScaledDamage);
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(
		TEXT("<Title>NEXT LEVEL</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Emits %d beams of lighting connecting with targets, repeatedly causing "
			"</><Damage>%d</><Default> Lighting damage with a chance to stun</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShockTargets),
		ScaledDamage);
}
