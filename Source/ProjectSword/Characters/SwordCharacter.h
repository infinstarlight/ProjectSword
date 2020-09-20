// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectSword/ProjectSword.h"
#include "ProjectSword/Abilities/SwordAbilityTypes.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "TimerManager.h"
#include "SwordCharacter.generated.h"


USTRUCT(BlueprintType)
struct PROJECTSWORD_API FSwordDamageNumber
{
	GENERATED_USTRUCT_BODY()

		float DamageAmount;

	FGameplayTagContainer Tags;

	FSwordDamageNumber() {}

	FSwordDamageNumber(float InDamageAmount, FGameplayTagContainer InTags) : DamageAmount(InDamageAmount)
	{
		// Copy tag container
		Tags.AppendTags(InTags);
	}
};

UCLASS()
class PROJECTSWORD_API ASwordCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordCharacter();

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class USwordAttributeSet* GetMainAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
		virtual bool IsAlive() const;

	// Switch on AbilityID to return individual ability levels.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
		virtual int32 GetAbilityLevel(ESwordAbilityInputID AbilityID) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentShield() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxShield() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetManaRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetStaminaRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentXP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetNextLevelXP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentGold() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Mouse
	void LookUp(float Value);

	// Gamepad
	void LookUpRate(float Value);

	// Mouse
	void Turn(float Value);

	// Gamepad
	void TurnRate(float Value);

	// Mouse + Gamepad
	void MoveForward(float Value);

	// Mouse + Gamepad
	void MoveRight(float Value);

	//// Toggles between perspectives
	//void TogglePerspective();


	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		float BaseTurnRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		float BaseLookUpRate;

	FGameplayTag DeadTag;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
		class USwordAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class USwordAttributeSet* MainAttributeSet;

	////Attribute changed callbacks
	//	virtual void HealthChanged(const FOnAttributeChangeData & Data);

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	bool bIsASCInputBound = false;

	//Called from SetupPlayerInputComponent, because we are required to use an Enum similar to Unity's old input system
	void BindASCInput();

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray < TSubclassOf<class USwordGameplayAbility>> CharacterAbilities;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray < TSubclassOf<class UGameplayEffect>> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/

	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);
	virtual void SetStamina(float Stamina);
	virtual void SetShield(float Shield);




private:

};
