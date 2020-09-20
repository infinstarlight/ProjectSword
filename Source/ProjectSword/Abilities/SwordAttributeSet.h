// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectSword/ProjectSword.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SwordAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class PROJECTSWORD_API USwordAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	//Constructor  
	USwordAttributeSet();

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (HideFromLevelInfos))
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, Damage)

	/*Current Health, when it is less than or equal to 0 we die, unless granted immunity
	Positive changes can directly use this
	Negative changes should go through Damage meta attribute*/
	UPROPERTY(BlueprintReadOnly, Category = "Health")
		FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CurrentHealth);

	//MaxHealth is its own attribute, we may want to modify it via GameplayEffects
	UPROPERTY(BlueprintReadOnly, Category = "Health")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MaxHealth)

		// Health regen rate will passively increase Mana every second
		UPROPERTY(BlueprintReadOnly, Category = "Health")
		FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, HealthRegenRate)

		/*Current Mana, when it is less than or equal to max mana, we start regenerating slowly
		Positive changes can directly use this
		Negative changes should go through Damage meta attribute*/
		UPROPERTY(BlueprintReadOnly, Category = "Mana")
		FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CurrentMana)

		//MaxMana is its own attribute, we may want to modify it via GameplayEffects
		UPROPERTY(BlueprintReadOnly, Category = "Mana")
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MaxMana)

		// Mana regen rate will passively increase Mana every second
		UPROPERTY(BlueprintReadOnly, Category = "Mana")
		FGameplayAttributeData ManaRegenRate;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, ManaRegenRate)

		/*Current Stamina, when it is less than or equal to 0 we cannot dodge roll, unless granted immunity
		Positive changes can directly use this
		Negative changes should go through Damage meta attribute*/
		UPROPERTY(BlueprintReadOnly, Category = "Stamina")
		FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CurrentStamina)

		//MaxStamina is its own attribute, we may want to modify it via GameplayEffects
		UPROPERTY(BlueprintReadOnly, Category = "Stamina")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MaxStamina)

		// Stamina regen rate will passively increase Stamina every second
		UPROPERTY(BlueprintReadOnly, Category = "Stamina")
		FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, StaminaRegenRate)

		// Current shield acts like temporary health. When depleted, damage will drain regular health.
		UPROPERTY(BlueprintReadOnly, Category = "Shield")
		FGameplayAttributeData CurrentShield;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CurrentShield)

		// Maximum shield that we can have.
		UPROPERTY(BlueprintReadOnly, Category = "Shield")
		FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MaxShield)

		// CurrentShield regen rate will passively increase CurrentShield every second
		UPROPERTY(BlueprintReadOnly, Category = "Shield")
		FGameplayAttributeData ShieldRegenRate;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, ShieldRegenRate)

		// Armor reduces the amount of damage done by attackers
		UPROPERTY(BlueprintReadOnly, Category = "Armor")
		FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, Armor)


		// MoveSpeed affects how fast characters can move.
		UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed")
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MoveSpeed)

		UPROPERTY(BlueprintReadOnly, Category = "Character Level")
		FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CharacterLevel)

		UPROPERTY(BlueprintReadOnly, Category = "Character Level")
		FGameplayAttributeData MaxCharacterLevel;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, MaxCharacterLevel)

		// Experience points gained from killing enemies. Used to level up (not implemented in this project).
		UPROPERTY(BlueprintReadOnly, Category = "XP")
		FGameplayAttributeData CurrentXP;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, CurrentXP)

		// Experience points needed for next level up.
		UPROPERTY(BlueprintReadOnly, Category = "XP")
		FGameplayAttributeData NextLevelUpXP;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, NextLevelUpXP)


		// Gold gained from killing enemies. Used to purchase items (not implemented in this project).
		UPROPERTY(BlueprintReadOnly, Category = "Gold")
		FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(USwordAttributeSet, Gold)

		virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:


	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
