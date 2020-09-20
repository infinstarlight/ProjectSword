// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectSword/ProjectSword.h"
#include "Subsystems/EngineSubsystem.h"
#include "SwordEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSWORD_API USwordEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
};
