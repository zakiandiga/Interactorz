// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQIInventory.generated.h"

UENUM(Blueprintable)
enum class EZAQIItemProcessType : uint8
{
	EIP_DROP UMETA(DisplayName = "Drop"),
	EIP_USE UMETA(DisplayName = "Use"),
	EIP_REMOVE UMETA(DisplayName = "Remove"),
	EIP_RETRIEVE UMETA(DisplayName = "Retrieve")
};

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_USTRUCT_BODY()

		//Item Data
		//Item Quantity
		//

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZAQOLINTERACTION_API UZAQIInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQIInventory();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
		TArray<FItemSlot> ActiveInventory = TArray<FItemSlot>();

		
};
