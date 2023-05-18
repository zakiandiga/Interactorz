// Copyright Zaki Agraraharja. All Rights Reserved.

#include "UI/WIPanelInventoryStorage.h"
#include "UI/WIPanelInventory.h"

void UWIPanelInventoryStorage::NativeConstruct()
{


	Super::NativeConstruct();
}

void UWIPanelInventoryStorage::OnPageOpened_Implementation(UWidget* OpenedWidget)
{
	switch (PanelInventoryMode)
	{
	default:
		break;
	case EPanelInventoryMode::EPI_Storage:
		//set title and button text
		break;
	case EPanelInventoryMode::EPI_Player:
		//set the same
		break;
	}
	Super::OnPageOpened_Implementation(OpenedWidget);
}

void UWIPanelInventoryStorage::OnPageClosed_Implementation(UWidget* ClosedWidget)
{
}
