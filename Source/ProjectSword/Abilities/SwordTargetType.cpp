// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordTargetType.h"
#include "ProjectSword/Characters/SwordCharacter.h"

USwordTargetType::USwordTargetType()
{

}

void USwordTargetType::GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	return;
}

USwordTargetType_UseOwner::USwordTargetType_UseOwner()
{

}

void USwordTargetType_UseOwner::GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	OutActors.Add(TargetingCharacter);
}

USwordTargetType_UseEventData::USwordTargetType_UseEventData()
{

}

void USwordTargetType_UseEventData::GetTargets_Implementation(ASwordCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FGameplayAbilityTargetDataHandle>& OutTargetData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
	if (FoundHitResult)
	{
		OutHitResults.Add(*FoundHitResult);
	}
	else if (EventData.Target)
	{
		OutActors.Add(const_cast<AActor*>(EventData.Target));
	}
}
