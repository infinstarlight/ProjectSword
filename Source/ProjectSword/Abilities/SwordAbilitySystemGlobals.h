// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "SwordAbilitySystemGlobals.generated.h"

/**
 * Child class of UAbilitySystemGlobals.
 * Do not try to get a reference to this or call into it during constructors of other UObjects. It will crash in packaged games.
 */
UCLASS()
class PROJECTSWORD_API USwordAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	USwordAbilitySystemGlobals();

	/**
* Cache commonly used tags here. This has the benefit of one place to set the tag FName in case tag names change and
* the function call into USwordAbilitySystemGlobals::GSGet() is cheaper than calling FGameplayTag::RequestGameplayTag().
* Classes can access them by USwordAbilitySystemGlobals::GSGet().DeadTag
* We're not using this in this sample project (classes are manually caching in their constructors), but it's here as a reference.
*/

	UPROPERTY()
		FGameplayTag DeadTag;


	static USwordAbilitySystemGlobals& GSGet()
	{
		//Safely convert
		return dynamic_cast<USwordAbilitySystemGlobals&>(Get());
	}

	///** Should allocate a project specific GameplayEffectContext struct. Caller is responsible for deallocation */
	//virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	virtual void InitGlobalTags() override;

	
};
