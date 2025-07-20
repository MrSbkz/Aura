// Copyright PK


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	while (true)
	{
		if (LevelUpInformation.Num() - 1 <= Level)
		{
			return Level;
		}

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			break;
		}
		
	}

	return Level;
}
