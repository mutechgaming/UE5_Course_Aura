// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilityTypes.h"
#include "AuraDamageGameplayAbility.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr); // ep. 305

	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass; 

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType; // ep. 303

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage; // ep. 303 Scalable floats would require a lvl input

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 20.f; // ep. 304

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.0f; // ep. 304

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequency = 1.0f; // ep. 304

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 5.0f; // ep. 304

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 1000.f; // ep. 312

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackForceMagnitude = 1000.f; // ep. 315

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackChance = 0.f; // ep. 315

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages);
}; 
