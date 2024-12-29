// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	virtual FString GetDescription(int32 Level); // ep. 293
	virtual FString GetNextLevelDescription(int32 Level); // ep. 293
	static FString GetLockedDescription(int32 Level); // ep. 293

protected: 

	float GetManaCost(float InLevel = 1.f); // ep. 295
	float GetCooldown(float InLevel = 1.f); // ep. 295
}; 
