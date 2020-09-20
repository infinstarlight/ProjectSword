// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// This header is included by all headers in the project so it's a good place to declare common includes
// We include EngineMinimal and the subset of engine headers used by most of our classes
// We don't want to include "Engine.h" as that pulls in too many classes we don't need and slows compile time
// ----------------------------------------------------------------------------------------------------------------

#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

PROJECTSWORD_API DECLARE_LOG_CATEGORY_EXTERN(LogProjectSword, Log, All);

UENUM(BlueprintType)
enum class ESwordAbilityInputID : uint8
{
	// 0 None
	None				UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm				UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel				UMETA(DisplayName = "Cancel"),
	// 3 Sprint
	Sprint				UMETA(DisplayName = "Sprint"),
	// 4 Jump
	Jump				UMETA(DisplayName = "Jump"),
	// 5 Dash
	Dash                UMETA(DisplayName = "Dash"),
	// 6 LightAttack
	LightAttack			UMETA(DisplayName = "Light Attack"),
	// 7 HeavyAttack
	HeavyAttack		UMETA(DisplayName = "Heavy Attack"),
	// 8 Cast Spell
	CastSpell		UMETA(DisplayName = "Cast Spell"),
	// 9 Block
	Block				UMETA(DisplayName = "Block"),
	// 10 NextWeapon
	NextWeapon			UMETA(DisplayName = "Next Weapon"),
	// 11 PrevWeapon
	PrevWeapon			UMETA(DisplayName = "Previous Weapon"),
	// 12 Interact
	Interact			UMETA(DisplayName = "Interact")
};