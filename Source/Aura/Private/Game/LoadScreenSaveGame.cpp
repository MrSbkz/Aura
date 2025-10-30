// Copyright PK


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithMapName(const FString& MapName)
{
	for (const FSavedMap& SavedMap : SavedMaps)
	{
		if (SavedMap.MapAssetName == MapName)
		{
			return SavedMap;
		}
	}

	return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& MapName)
{
	for (const FSavedMap& SavedMap : SavedMaps)
	{
		if (SavedMap.MapAssetName == MapName)
		{
			return true;
		}
	}

	return false;
}
