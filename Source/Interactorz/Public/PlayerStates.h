#pragma once

UENUM(BlueprintType)
enum class EPlayerControlStates : uint8
{
	EPC_OnCharacter UMETA(DisplayName = "OnCharacter"),
	EPC_Interacting UMETA(DisplayName = "Interacting"),
	EPC_OnMenu UMETA(DisplayName = "OnMenu")
};