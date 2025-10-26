// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

UENUM(BlueprintType)
enum class ESaveSlotStatus : uint8
{
	Vacant,
	EnterName,
	Taken
};

/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SlotName = FString();
	
	UPROPERTY()
	FString MapName = FString("Default Map Name");
	
	UPROPERTY()
	int32 IndexSlot = 0;

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = ESaveSlotStatus::Vacant;

	UPROPERTY()
	FName PlayerStartTag = FName();

	UPROPERTY()
	bool bFirstTimeLoadIn = true;

	/* Player */

	UPROPERTY()
	int32 PlayerLevel = 0;

	UPROPERTY()
	int32 XP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;

	/* Attributes */

	UPROPERTY()
	float Strength = 0.0;

	UPROPERTY()
	float Intelligence = 0.0;

	UPROPERTY()
	float Resilience = 0.0;

	UPROPERTY()
	float Vigor = 0.0;
};
