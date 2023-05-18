// Copyright Zaki Agraraharja. All Rights Reserved.


#include "UI/WIActionLogEntry.h"
#include "Components/TextBlock.h"

void UWIActionLogEntry::SetActionLogText(FString LogText)
{
	ActionLogText->SetText(FText::FromString(LogText));
}
