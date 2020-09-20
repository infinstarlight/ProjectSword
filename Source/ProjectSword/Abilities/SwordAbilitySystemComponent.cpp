// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

USwordAbilitySystemComponent::USwordAbilitySystemComponent()
{

}

bool USwordAbilitySystemComponent::GetShouldTick() const
{
	return Super::GetShouldTick();
}

void USwordAbilitySystemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



USwordAbilitySystemComponent* USwordAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<USwordAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}

void USwordAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{



	// Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
	if (IsGenericConfirmInputBound(InputID))
	{
		LocalInputConfirm();
		return;
	}

	if (IsGenericCancelInputBound(InputID))
	{
		LocalInputCancel();
		return;
	}

	// ---------------------------------------------------------

	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.InputID == InputID)
		{
			if (Spec.Ability)
			{
				Spec.InputPressed = true;
				if (Spec.IsActive())
				{
					if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
					{
						ServerSetInputPressed(Spec.Handle);
					}

					AbilitySpecInputPressed(Spec);

					// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
				}
				else
				{
					//	UGSGameplayAbility* GA = Cast<UGSGameplayAbility>(Spec.Ability);
					//	if (GA && GA->bActivateOnInput)
					//	{
					//		// Ability is not active, so try to activate it
					//		TryActivateAbility(Spec.Handle);
					//	}
					//}
				}
			}
		}
	}
}

int32 USwordAbilitySystemComponent::K2_GetTagCount(FGameplayTag TagToCheck) const
{
	return GetTagCount(TagToCheck);
}

FGameplayAbilitySpecHandle USwordAbilitySystemComponent::FindAbilitySpecHandleForClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject /*= nullptr*/)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		TSubclassOf<UGameplayAbility> SpecAbilityClass = Spec.Ability->GetClass();
		if (SpecAbilityClass == AbilityClass)
		{
			if (!OptionalSourceObject || (OptionalSourceObject && Spec.SourceObject == OptionalSourceObject))
			{
				return Spec.Handle;
			}
				
		}
	}
	return FGameplayAbilitySpecHandle();
}
