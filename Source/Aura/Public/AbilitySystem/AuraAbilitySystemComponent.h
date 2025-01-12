// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"
 
class UGameplayAbility;
struct FGameplayTag;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*AbilityLevel*/); // ep. 285, 291
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, FGameplayTag /*AbilityTag*/, FGameplayTag /*Status*/, FGameplayTag /*Slot*/, FGameplayTag /*PreviousSlot*/); // ep. 299
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, FGameplayTag /*AbilityTag*/); // ep. 339
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveEffect, FGameplayTag /*AbilityTag*/, bool /*bActivate*/); // ep. 344
/**
 * 
 */

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged; // ep. 285
	FAbilityEquipped AbilityEquipped; // ep. 299
	FDeactivatePassiveAbility DeactivatePassiveAbility; // ep. 338
	FActivatePassiveEffect ActivatePassiveEffect; // ep. 344


	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagPressed(const FGameplayTag& InputTag); // ep. 320
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate); 
	
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastActivatePassiveEffect(FGameplayTag AbilityTag, bool bActivate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	bool SlotIsEmpty(const FGameplayTag& Slot); // ep. 343
	static bool AbilityHasSlot(const FGameplayAbilitySpec& Spec, const FGameplayTag& Slot); // ep. 343
	static bool AbilityHasAnySlot(const FGameplayAbilitySpec& Spec); // ep. 343
	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec); // ep. 343
	
	void AssignSlotToAbility(FGameplayAbilitySpec& Spec, FGameplayTag Slot); // ep 343
	
	FGameplayTag GetStatusFromAbilityTag(FGameplayTag AbilityTag); // ep. 299
	FGameplayTag GetInputTagFromAbilityTag(FGameplayTag AbilityTag); // ep. 299

	FGameplayAbilitySpec* GetSpecFromAbilityTag(FGameplayTag AbilityTag); // ep. 284
	FGameplayAbilitySpec* GetSpecWithSlot(FGameplayTag Slot); // ep. 343

	void UpgradeAttributes(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	void UpdateAbilityStatus(int32 Level); // ep. 284

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag); // ep. 291

	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(FGameplayTag AbilityTag, FGameplayTag Slot); // ep. 299

	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(FGameplayTag AbilityTag, FGameplayTag Status, FGameplayTag Slot, FGameplayTag PreviousSlot); // ep. 299
 
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);  // ep. 293
	
	void ClearSlot(FGameplayAbilitySpec* Spec); // ep. 299

	void ClearAbilitiesOfSlot(FGameplayTag Slot); // ep. 299

	bool AbilityHasSlot(FGameplayAbilitySpec* Spec, FGameplayTag Slot); // ep. 299

protected:

	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel); // ep. 291
}; 
