// Copyright Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquippedButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString); // ep. 289, 293
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, FGameplayTag, AbilityType); // ep. 298


struct FSelectedAbility // ep. 290
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChanged; // ep. 286

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate; // ep. 289

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipDelegate; // ep. 298

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitingForEquipDelegate; // ep. 298

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	UFUNCTION(BlueprintCallable)
	void GlobeDeselect(); // ep. 297

	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed(); // ep. 298

private:

	static void ShouldEnableButtons(FGameplayTag AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpendPointsButton, bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility 
	{ 
		FAuraGameplayTags::Get().Abilities_None, 
		FAuraGameplayTags::Get().Abilities_Status_Locked 
	};

	int32 CurrentSpellPoints = 0;

	bool bWaitingForEquipSelection = false;
};
