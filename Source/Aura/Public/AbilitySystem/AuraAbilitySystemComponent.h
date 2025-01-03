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
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, FGameplayTag /*AbilityTag*/, FGameplayTag /*Status*/, FGameplayTag /*Slot*/, FGameplayTag /*PreviousSlot*/) // ep. 299

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

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate); 

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayTag GetStatusFromAbilityTag(FGameplayTag AbilityTag); // ep. 299
	FGameplayTag GetInputTagFromAbilityTag(FGameplayTag AbilityTag); // ep. 299

	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag); // ep. 284

	void UpgradeAttributes(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	void UpdateAbilityStatus(int32 Level); // ep. 284

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag); // ep. 291

	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(FGameplayTag AbilityTag, FGameplayTag Slot); // ep. 299

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
