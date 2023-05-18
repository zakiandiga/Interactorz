// Copyright Zaki Agraraharja. All Rights Reserved.


#include "UI/WIPanelInventoryPlayerMenu.h"
#include "UI/WIInGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryEntryDataContainer.h"
#include "Components/PanelWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "DAItemData.h"
#include "Inventory.h"

void UWIPanelInventoryPlayerMenu::NativeConstruct()
{
	Super::NativeConstruct();
	UWIInGameMenu* Parent = Cast<UWIInGameMenu>(GetParent()->GetOuter()->GetOuter());

	if (Parent == nullptr) return;

	Parent->OnMenuCreated.AddDynamic(this, &UWIPanelInventoryPlayerMenu::AssignOwnerInventory);
	DescriptionText->SetText(FText());
}


