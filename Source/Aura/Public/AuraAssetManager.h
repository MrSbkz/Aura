// Copyright PK

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 *  To register the AuraAssetManager open Config/DefaultEngine.ini
 *  Add new row "AssetManagerClassName=/Script/Aura.AuraAssetManager"
 *  to [/Script/Engine.Engine] section
 *  
 *  Branch: 87-aura-asset-manager
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UAuraAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
