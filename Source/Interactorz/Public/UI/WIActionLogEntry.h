// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WIActionLogEntry.generated.h"

class UTextBlock;
UCLASS()
class INTERACTORZ_API UWIActionLogEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ActionLogText;

public:
	UFUNCTION(BlueprintCallable, Category = "ActionLog")
	void SetActionLogText(FString LogText);
	
};
