// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WIPanelInventory.h"
#include "WIPanelInventoryStorage.generated.h"

UENUM(Blueprintable)
enum class EPanelInventoryMode : uint8
{
	EPI_Storage UMETA(DisplayName = "Storage"),
	EPI_Player UMETA(DisplayName = "Player")	
};

UCLASS()
class INTERACTORZ_API UWIPanelInventoryStorage : public UWIPanelInventory
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Inventory | Storage")
	EPanelInventoryMode PanelInventoryMode = EPanelInventoryMode::EPI_Storage;

	void NativeConstruct() override;

public:
	void OnPageOpened_Implementation(UWidget* OpenedWidget) override;
	void OnPageClosed_Implementation(UWidget* ClosedWidget) override;
};
