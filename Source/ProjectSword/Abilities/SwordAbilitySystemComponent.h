// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SwordAbilitySystemComponent.generated.h"


UCLASS()
class PROJECTSWORD_API USwordAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USwordAbilitySystemComponent();

	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	virtual bool GetShouldTick() const override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// Version of function in AbilitySystemGlobals that returns correct type
	static USwordAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent);

	// Input bound to an ability is pressed
	virtual void AbilityLocalInputPressed(int32 InputID) override;

	// Exposes GetTagCount to Blueprint
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities", Meta = (DisplayName = "GetTagCount", ScriptName = "GetTagCount"))
		int32 K2_GetTagCount(FGameplayTag TagToCheck) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
		FGameplayAbilitySpecHandle FindAbilitySpecHandleForClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject = nullptr);
};
