// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SAT_PlayMontageAndWait.generated.h"

class USwordAbilitySystemComponent;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSwordPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */
UCLASS()
class PROJECTSWORD_API USAT_PlayMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()
	
};
