// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBaseWeapon.h"
#include "ProjectSword/Abilities/SwordAbilitySystemComponent.h"
#include "ProjectSword/Abilities/SwordAbilitySystemGlobals.h"

// Sets default values
ASwordBaseWeapon::ASwordBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

class UAbilitySystemComponent* ASwordBaseWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASwordBaseWeapon::Equip()
{

}

void ASwordBaseWeapon::UnEquip()
{

}

void ASwordBaseWeapon::AddAbilities()
{

}

void ASwordBaseWeapon::RemoveAbilities()
{

}

int32 ASwordBaseWeapon::GetAbilityLevel(ESwordAbilityInputID AbilityID)
{
	// All abilities for now are level 1
	return 1;
}

// Called when the game starts or when spawned
void ASwordBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwordBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

