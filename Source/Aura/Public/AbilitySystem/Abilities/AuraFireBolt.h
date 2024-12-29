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
};
