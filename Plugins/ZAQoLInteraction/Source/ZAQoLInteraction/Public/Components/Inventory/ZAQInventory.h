// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInventory.generated.h"

UENUM(Blueprintable)
enum class EZAQItemProcessType : uint8
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

	FString Item;
	int32 Quantity;
	float TotalWeight() { return Quantity; }

};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZAQOLINTERACTION_API UZAQInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInventory();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	TArray<FItemSlot> ActiveInventory = TArray<FItemSlot>();

		
};
