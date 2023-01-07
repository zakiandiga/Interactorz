// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAction.h"
#include "DAItemData.h"
#include "DebugHelpers/DebugMacros.h"

void UItemAction::UseItem_Implementation(UDAItemData* UsedItem, AActor* ItemUser)
{
	FString Message = FString::Printf(TEXT("Used %s"), *UsedItem->ItemData.Name);
	SCREEN_LOG(Message, FColor::Green);

}
