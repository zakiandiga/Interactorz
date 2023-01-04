// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Consumables UMETA(DisplayName = "Consumables"),
	EIT_Materials UMETA(DisplayName = "Materials"),
	EIT_Parts UMETA(DisplayName = "Parts"),
	EIT_Equipments UMETA(DisplayName = "Equipments"),
	EIT_Quest UMETA(DisplayName = "Quest"),
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
		
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	bool bIsStackable = true;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType = EItemType::EIT_Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* PickUpSprite = nullptr;
};

UCLASS(BlueprintType)
class INTERACTORZ_API UDA_ItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FItemData ItemData;
	
};

