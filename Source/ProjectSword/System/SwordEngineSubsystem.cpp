// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEngineSubsystem.h"
#include "AbilitySystemGlobals.h"

void USwordEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAbilitySystemGlobals::Get().InitGlobalData();
}
