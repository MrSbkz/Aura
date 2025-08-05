// Copyright PK

#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Kismet/KismetSystemLibrary.h"


void UAuraFireBolt::SpawnProjectiles(
	const FVector& ProjectileTargetLocation,
	const FGameplayTag& SocketTag,
	bool bOverridePitch,
	float PitchOverride,
	AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2, FVector::UpVector);

	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());

	if (NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; ++i)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0.f, 0.f, 10.f);
			UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				Start,
				Start + Direction * 100.f,
				1.f,
				FLinearColor::Red,
				120.f,
				1.f);
		}
	}
	else
	{
		const FVector Start = SocketLocation + FVector(0.f, 0.f, 10.f);
		UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			Start,
			Start + Forward * 100.f,
			1.f,
			FLinearColor::Red,
			120.f,
			1.f);
	}

	// UKismetSystemLibrary::DrawDebugArrow(
	// 	GetAvatarActorFromActorInfo(),
	// 	SocketLocation,
	// 	SocketLocation + Forward * 100.f,
	// 	2.f,
	// 	FLinearColor::White,
	// 	120.f,
	// 	2.f);
	//
	// UKismetSystemLibrary::DrawDebugArrow(
	// 	GetAvatarActorFromActorInfo(),
	// 	SocketLocation,
	// 	SocketLocation + LeftOfSpread * 100.f,
	// 	2.f,
	// 	FLinearColor::Gray,
	// 	120.f,
	// 	2.f);
	//
	// UKismetSystemLibrary::DrawDebugArrow(
	// 	GetAvatarActorFromActorInfo(),
	// 	SocketLocation,
	// 	SocketLocation + RightOfSpread * 100.f,
	// 	2.f,
	// 	FLinearColor::Gray,
	// 	120.f,
	// 	2.f);
}

FString UAuraFireBolt::GetDescription(const int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>FIRE BOLT</>\n\n"
				"<Small>Level: </><Level>%d</>\n"
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				"<Default>Launched a bolt of fire, exploding on impact and dealing "
				"</><Damage>%d</><Default> fire damage with a chance to burn</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage
		);
	}

	return FString::Printf(
		TEXT("<Title>FIRE BOLT</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launched %d bolts of fire, exploding on impact and dealing "
			"</><Damage>%d</><Default> fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(const int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(
		TEXT("<Title>NEW LEVEL</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launched %d bolts of fire, exploding on impact and dealing "
			"</><Damage>%d</><Default> fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);
}
