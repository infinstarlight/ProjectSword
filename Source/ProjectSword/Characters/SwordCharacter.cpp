// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordCharacter.h"
#include "ProjectSword/Abilities/SwordAttributeSet.h"
#include "ProjectSword/Abilities/SwordAbilitySystemComponent.h"
#include "ProjectSword/Abilities/SwordGameplayAbility.h"
#include "ProjectSword/Abilities/SwordAbilitySystemGlobals.h"
#include "ProjectSword/Weapons/SwordBaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASwordCharacter::ASwordCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create ability system component
	AbilitySystemComponent = CreateDefaultSubobject<USwordAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	//Create attribute set
	MainAttributeSet = CreateDefaultSubobject<USwordAttributeSet>(TEXT("MainAttributeSet"));

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

class UAbilitySystemComponent* ASwordCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

class USwordAttributeSet* ASwordCharacter::GetMainAttributeSet() const
{
	return MainAttributeSet;
}

bool ASwordCharacter::IsAlive() const
{
	return GetCurrentHealth() > 0.0f;
}

int32 ASwordCharacter::GetAbilityLevel(ESwordAbilityInputID AbilityID) const
{
	return 1;
}

int32 ASwordCharacter::GetCharacterLevel() const
{
	return MainAttributeSet->GetCharacterLevel();
}

float ASwordCharacter::GetCurrentHealth() const
{
	return MainAttributeSet->GetCurrentHealth();
}

float ASwordCharacter::GetMaxHealth() const
{
	return MainAttributeSet->GetMaxHealth();
}

float ASwordCharacter::GetCurrentShield() const
{
	return MainAttributeSet->GetCurrentShield();
}

float ASwordCharacter::GetMaxShield() const
{
	return MainAttributeSet->GetMaxShield();
}

float ASwordCharacter::GetHealthRegenRate() const
{
	return MainAttributeSet->GetHealthRegenRate();
}

float ASwordCharacter::GetCurrentMana() const
{
	return MainAttributeSet->GetCurrentMana();
}

float ASwordCharacter::GetMaxMana() const
{
	return MainAttributeSet->GetMaxMana();
}

float ASwordCharacter::GetManaRegenRate() const
{
	return MainAttributeSet->GetManaRegenRate();
}

float ASwordCharacter::GetCurrentStamina() const
{
	return MainAttributeSet->GetCurrentStamina();
}

float ASwordCharacter::GetMaxStamina() const
{
	return MainAttributeSet->GetMaxStamina();
}

float ASwordCharacter::GetStaminaRegenRate() const
{
	return MainAttributeSet->GetStaminaRegenRate();
}

float ASwordCharacter::GetCurrentXP() const
{
	return MainAttributeSet->GetCurrentXP();
}

float ASwordCharacter::GetNextLevelXP() const
{
	return MainAttributeSet->GetNextLevelUpXP();
}

float ASwordCharacter::GetCurrentGold() const
{
	return MainAttributeSet->GetGold();
}

// Called when the game starts or when spawned
void ASwordCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();

	AddStartupEffects();

	AddCharacterAbilities();


	if (AbilitySystemComponent->GetTagCount(DeadTag) > 0)
	{
		// Set Health/Mana/Stamina to their max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());
		SetShield(GetMaxShield());
	}

	// Remove Dead tag
	AbilitySystemComponent->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(DeadTag));

}

void ASwordCharacter::AddCharacterAbilities()
{
	for (TSubclassOf<USwordGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}
}

void ASwordCharacter::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	if (DefaultAttributes.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	/*for (TSubclassOf<UGameplayEffect> GameplayEffect : DefaultAttributes)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}*/
}

void ASwordCharacter::AddStartupEffects()
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void ASwordCharacter::BindASCInput()
{
	if (!bIsASCInputBound && IsValid(AbilitySystemComponent) && IsValid(InputComponent))
	{
		// Bind to AbilitySystemComponent
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("ESwordAbilityInputID"), static_cast<int32>(ESwordAbilityInputID::Confirm), static_cast<int32>(ESwordAbilityInputID::Cancel)));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Jump"), FString("Jump"), FString("ESwordAbilityInputID"), static_cast<int32>(ESwordAbilityInputID::Jump)));
		bIsASCInputBound = true;
	}

}

void ASwordCharacter::SetHealth(float Health)
{
	if (IsValid(MainAttributeSet))
	{
		MainAttributeSet->SetCurrentHealth(Health);
	}
}

void ASwordCharacter::SetMana(float Mana)
{
	if (IsValid(MainAttributeSet))
	{
		MainAttributeSet->SetCurrentMana(Mana);
	}
}

void ASwordCharacter::SetStamina(float Stamina)
{
	if (IsValid(MainAttributeSet))
	{
		MainAttributeSet->SetCurrentStamina(Stamina);
	}
}

void ASwordCharacter::SetShield(float Shield)
{
	if (IsValid(MainAttributeSet))
	{
		MainAttributeSet->SetCurrentShield(Shield);
	}
}

// Called every frame
void ASwordCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASwordCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASwordCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwordCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ASwordCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASwordCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ASwordCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASwordCharacter::TurnRate);

	BindASCInput();

}

void ASwordCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void ASwordCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ASwordCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void ASwordCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ASwordCharacter::MoveForward(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ASwordCharacter::MoveRight(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ASwordCharacter::RemoveCharacterAbilities()
{
	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

