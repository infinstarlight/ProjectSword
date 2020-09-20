// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordGameplayAbility.h"
#include "SwordAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "SwordTargetType.h"
#include "GameplayTagContainer.h"
#include "ProjectSword/Characters/SwordCharacter.h"
#include "GameplayTagContainer.h"
#include "SwordAbilityTypes.h"


USwordGameplayAbility::USwordGameplayAbility()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	bActivateAbilityOnGranted = false;
	bActivateOnInput = true;
	bSourceObjectMustEqualCurrentWeaponToActivate = false;
	bCannotActivateWhileInteracting = true;
	// UGSAbilitySystemGlobals hasn't initialized tags yet to set ActivationBlockedTags
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Dead"));
}

void USwordGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

FGameplayAbilityTargetDataHandle USwordGameplayAbility::MakeGameplayAbilityTargetDataHandleFromActorArray(const TArray<AActor*> TargetActors)
{
	if (TargetActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
		NewData->TargetActorArray.Append(TargetActors);
		return FGameplayAbilityTargetDataHandle(NewData);
	}

	return FGameplayAbilityTargetDataHandle();
}

FGameplayAbilityTargetDataHandle USwordGameplayAbility::MakeGameplayAbilityTargetDataHandleFromHitResults(const TArray<FHitResult> HitResults)
{
	FGameplayAbilityTargetDataHandle TargetData;

	for (const FHitResult& HitResult : HitResults)
	{
		FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
		TargetData.Add(NewData);
	}

	return TargetData;
}

FSwordGameplayEffectContainerSpec USwordGameplayAbility::MakeEffectContainerSpecFromContainer(const FSwordGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	//First, get actor info
	FSwordGameplayEffectContainerSpec ReturnSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	AActor* AvatarActor = GetOwningActorFromActorInfo();
	ASwordCharacter* AvatarCharacter = Cast<ASwordCharacter>(AvatarActor);
	USwordAbilitySystemComponent* OwningASC = USwordAbilitySystemComponent::GetAbilitySystemComponentFromActor(OwningActor, false);

	if (OwningASC)
	{
		//If we have a target type, run the targeting logic. This isn't necessary, targets can be added later
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;

			TArray<FGameplayAbilityTargetDataHandle> TargetData;
			const USwordTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			TargetTypeCDO->GetTargets(AvatarCharacter, AvatarActor, EventData, TargetData, HitResults, TargetActors);
			ReturnSpec.AddTargets(TargetData, HitResults, TargetActors);
		}

		//If we don't have an override level, use the ability level
		if (OverrideGameplayLevel == INDEX_NONE)
		{
			OverrideGameplayLevel = GetAbilityLevel();
		}

		// Build GameplayEffectSpecs for each applied effect
		for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		{
			//ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideGameplayLevel));
		}
	}
	return ReturnSpec;
}


FSwordGameplayEffectContainerSpec USwordGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel /*= -1*/)
{
	FSwordGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);

	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideGameplayLevel);
	}
	return FSwordGameplayEffectContainerSpec();
}

UObject* USwordGameplayAbility::K2_GetSourceObject(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const
{
	return GetSourceObject(Handle, &ActorInfo);
}

TArray<FActiveGameplayEffectHandle> USwordGameplayAbility::ApplyEffectContainerSpec(const FSwordGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;

	//// Iterate list of effect specs and apply them to their target data
	//for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	//{
	//	AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	//}
	return AllEffects;
}


FString USwordGameplayAbility::GetCurrentPredictionKeyStatus()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	return ASC->ScopedPredictionKey.ToString() + " is valid for more prediction: " + (ASC->ScopedPredictionKey.IsValidForMorePrediction() ? TEXT("true") : TEXT("false"));
}

bool USwordGameplayAbility::IsPredictionKeyValidForMorePrediction() const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	return ASC->ScopedPredictionKey.IsValidForMorePrediction();
}

bool USwordGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (bCannotActivateWhileInteracting)
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (ASC->GetTagCount(InteractingTag) > ASC->GetTagCount(InteractingRemovalTag))
		{
			return false;
		}
	}

	if (bSourceObjectMustEqualCurrentWeaponToActivate)
	{
		ASwordCharacter* Character = Cast<ASwordCharacter>(ActorInfo->AvatarActor);
		//if (Character && Character->GetCurrentWeapon() && (UObject*)Character->GetCurrentWeapon() == GetSourceObject(Handle, ActorInfo))
		{

		}
	}

	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

bool USwordGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags) && SwordCheckCost(Handle, *ActorInfo);
}

bool USwordGameplayAbility::SwordCheckCost_Implementation(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const
{
	return true;
}

void USwordGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	SwordApplyCost(Handle, *ActorInfo, ActivationInfo);
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USwordGameplayAbility::SendTargetDataToServer(const FGameplayAbilityTargetDataHandle& TargetData)
{
	if (IsPredictingClient())
	{
		UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
		check(ASC);

		FScopedPredictionWindow ScopedPrediction(ASC, IsPredictingClient());

		FGameplayTag ApplicaationTag; // TODO: Where is this useful?
		CurrentActorInfo->AbilitySystemComponent->CallServerSetReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey(), TargetData, ApplicaationTag, ASC->ScopedPredictionKey);
	}
}

bool USwordGameplayAbility::IsInputPressed() const
{
	FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec();
	return Spec && Spec->InputPressed;
}
