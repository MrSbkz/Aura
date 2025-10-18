// Copyright PK


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	auto TestValue = SlotStatus.GetIntValue();
	SetWidgetSwitcherIndex.Broadcast(SlotStatus.GetIntValue());
}

void UMVVM_LoadSlot::SetPlayerName(const FString& InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}
