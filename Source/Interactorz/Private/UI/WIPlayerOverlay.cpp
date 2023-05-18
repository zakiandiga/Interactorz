// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIPlayerOverlay.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Inventory.h"
#include "Character/PlayerCharacter.h"

void UWIPlayerOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerInventory = Cast<APlayerCharacter>(GetOwningPlayer()->GetPawn())->GetInventory();
	
	if (PlayerInventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInventory is Null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerInventory is NOT Null"));

	PlayerInventory->OnItemRetrieved.AddDynamic(this, &UWIPlayerOverlay::ItemRetrievedDelegate);
	PlayerInventory->OnItemRemoved.AddDynamic(this, &UWIPlayerOverlay::ItemRemovedDelegate);
	PlayerInventory->OnItemDropped.AddDynamic(this, &UWIPlayerOverlay::ItemDroppedDelegate);
	PlayerInventory->OnItemUsed.AddDynamic(this, &UWIPlayerOverlay::ItemUsedDelegate);
	PlayerInventory->OnInventoryIsFull.AddDynamic(this, &UWIPlayerOverlay::InventoryIsFull);
}

void UWIPlayerOverlay::ItemRetrievedDelegate(FString Item, int32 Quantity)
{
	ItemRetrieved(Item, Quantity);
}

void UWIPlayerOverlay::ItemRemovedDelegate(FString Item, int32 Quantity)
{
	ItemRemoved(Item, Quantity);
}

void UWIPlayerOverlay::ItemDroppedDelegate(FString Item, int32 Quantity)
{
	ItemDropped(Item, Quantity);
}

void UWIPlayerOverlay::ItemUsedDelegate(FString Item, int32 Quantity)
{
	ItemUsed(Item, Quantity);
}

void UWIPlayerOverlay::SetInteractableInfoPanelVisible(FString InteractableNameToSet)
{
	InteractableInfoText->SetText(FText::FromString(InteractableNameToSet));
	InteractableInfoPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWIPlayerOverlay::SetInteractableInfoPanelHidden(FString InteractableNameToRemove)
{
	InteractableInfoText->SetText(FText());
	InteractableInfoPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UWIPlayerOverlay::ItemRetrieved_Implementation(const FString& ItemName, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Retrieved CPP implementation"));
}

void UWIPlayerOverlay::ItemRemoved_Implementation(const FString& ItemName, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Item removed CPP implementation"));
}

void UWIPlayerOverlay::ItemDropped_Implementation(const FString& ItemName, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Item dropped CPP implementation"));
}

void UWIPlayerOverlay::ItemUsed_Implementation(const FString& ItemName, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("Item used CPP implementation"));
}

void UWIPlayerOverlay::InventoryIsFull_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory is FULL CPP"));
}

