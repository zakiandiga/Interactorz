// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIMainMenu.h"

void UWIMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Error, TEXT("NativeConstruct() called"));
	//set input UIOnly
	//enable mouse
}

void UWIMainMenu::NativeDestruct()
{
	Super::NativeDestruct();
	UE_LOG(LogTemp, Error, TEXT("Main menu NativeDestruct() called!"));
}
