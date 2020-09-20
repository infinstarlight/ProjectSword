// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbilityTypes.h"
#include "ProjectSword/Abilities/SwordAbilityTypes.h"
#include "SwordTargetType.generated.h"

class ASwordCharacter;
class AActor;
struct FGameplayEventData;

/**
 * Class that is used to determine targeting for abilities
 * It is meant to be blueprinted to run target logic
 * This does not subclass GameplayAbilityTargetActor because this class is never instanced into the world
 * This can be used as a basis for a game-specific targeting blueprint
 * If your targeting is more complicated you may need to instance into the world once or as a pooled actor
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class PROJECTSWORD_API USwordTargetType : public UObject
{
	GENERATED_BODY()
public:

	USwordTargetType();

	//Called to determine targets to apply gameplay effects to
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
	virtual void GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

//Trivial target type that uses the owner
UCLASS(NotBlueprintable)
class PROJECTSWORD_API USwordTargetType_UseOwner : public USwordTargetType
{
	GENERATED_BODY()

public:

	USwordTargetType_UseOwner();

	//uses the passed in event data
	virtual void GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

//Trivial target type that pulls that target out of the event data
UCLASS(NotBlueprintable)
class PROJECTSWORD_API USwordTargetType_UseEventData : public USwordTargetType
{
	GENERATED_BODY()

public:

	USwordTargetType_UseEventData();

	//Uses the passed in event data
	virtual void GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
