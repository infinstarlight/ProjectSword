// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAbilitySystemGlobals.h"

USwordAbilitySystemGlobals::USwordAbilitySystemGlobals()
{

}

//FGameplayEffectContext* USwordAbilitySystemGlobals::AllocGameplayEffectContext() const
//{
//	return new FGSGameplayEffectContext();
//}

void USwordAbilitySystemGlobals::InitGlobalTags()
{
	
	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}
