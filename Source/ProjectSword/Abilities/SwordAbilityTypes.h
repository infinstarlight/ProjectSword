#pragma once

// ----------------------------------------------------------------------------------------------------------------
// This header is for Ability-specific structures and enums that are shared across a project
// Every game will probably need a file like this to handle their extensions to the system
// This file is a good place for subclasses of FGameplayEffectContext and FGameplayAbilityTargetData
// ----------------------------------------------------------------------------------------------------------------

#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEffectStackChange.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEffectRemoved.h"
#include "SwordAbilityTypes.generated.h"

class USwordAbilitySystemComponent;
class UGameplayEffect;
class USwordTargetType;

/**
 * Struct defining a list of gameplay effects, a tag, and targeting info
 * These containers are defined statically in blueprints or assets and then turn into Specs at runtime
 */
USTRUCT(BlueprintType)
struct FSwordGameplayEffectContainer
{
	GENERATED_BODY()

public:

	FSwordGameplayEffectContainer() {}

	/** Sets the way that targeting happens */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
		TSubclassOf<USwordTargetType> TargetType;

	/** List of gameplay effects to apply to the targets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
		TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

//A "processed" version of SwordGameplayEffectContainer than can be passed around and eventually applied
USTRUCT(BlueprintType)
struct FSwordGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:

	FSwordGameplayEffectContainerSpec() {}

	//Computed target data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;

	//List of gameplay effects to apply to the targets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<FGameplayAbilitySpecHandle> TargetGameplayEffectSpecs;

	//Returns true if this has any valid effect specs
	bool HasValidEffects() const;
		
	//Returns true if this has any valid targets
	bool HasValidTargets() const;

	//Adds new targets to target data
	void AddTargets(const TArray<FGameplayAbilityTargetDataHandle>& InTargetData, const TArray<FHitResult>& HitResults, const TArray<AActor*> TargetActors);

	//Clears target data
	void ClearTargets();
};


