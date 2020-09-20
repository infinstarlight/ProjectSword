// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SwordCharacter.h"
#include "SwordPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSWORD_API ASwordPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


	/*UFUNCTION(Client, Reliable, WithValidation)
		void ShowDamageNumber(float DamageAmount, ASwordCharacter* TargetCharacter, FGameplayTagContainer DamageNumberTags);
	void ShowDamageNumber_Implementation(float DamageAmount, ASwordCharacter* TargetCharacter, FGameplayTagContainer DamageNumberTags);
	bool ShowDamageNumber_Validate(float DamageAmount, ASwordCharacter* TargetCharacter, FGameplayTagContainer DamageNumberTags);*/
	
};
