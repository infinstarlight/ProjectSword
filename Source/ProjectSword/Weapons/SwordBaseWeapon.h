// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "ProjectSword/ProjectSword.h"
#include "SwordBaseWeapon.generated.h"

class UAnimMontage;
class USwordAbilitySystemComponent;
class USwordGameplayAbility;
class ASwordCharacter;

UCLASS(Blueprintable,BlueprintType)
class PROJECTSWORD_API ASwordBaseWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordBaseWeapon();

	//This tag is used to determine which animations to use 
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GASShooter|GSWeapon")
		FGameplayTag WeaponTag;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called when the player equips this weapon
	virtual void Equip();

	// Called when the player unequips this weapon
	virtual void UnEquip();

	virtual void AddAbilities();

	virtual void RemoveAbilities();

	virtual int32 GetAbilityLevel(ESwordAbilityInputID AbilityID);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USwordAbilitySystemComponent* AbilitySystemComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
