// Copyright Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraGameplayTags.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()
	
public:

	virtual FString GetDescription(int32 Level) override; // ep. 294
	virtual FString GetNextLevelDescription(int32 Level) override; // ep. 294

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(FVector ProjectileTargetLocation, FGameplayTag SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget); // ep. 316


protected: 

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	float ProjectileSpread = 90.f;  // ep. 316

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	int32 MaxNumProjectiles = 5.f;  // ep. 316

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	float HomingAccelerationMin = 1600.f; // ep. 318

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	float HomingAccelerationMax = 3200.f; // ep. 318

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	bool bLaunchHomingProjectiles = true;
};
