// Copyright Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams // ep. 305, 315
{
	GENERATED_BODY()

	FDamageEffectParams() {}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr; 

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();

	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffChance = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.f; // ep. 312

	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector; // ep. 312

	UPROPERTY(BlueprintReadWrite)
	float KnockbackForceMagnitude = 0.f; // ep. 315

	UPROPERTY(BlueprintReadWrite)
	float KnockbackChance = 0.f; // ep. 315

	UPROPERTY(BlueprintReadWrite)
	FVector KnockbackForce = FVector::ZeroVector; // ep. 315
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool isCriticalHit() const { return bIsCriticalHit; }
	bool isBlockedHit() const { return bIsBlockedHit; }
	bool isSuccessfulDebuff() const { return bIsSuccessfulDebuff; }  // ep. 308
	float GetDebuffDamage() const { return DebuffDamage; }  // ep. 308
	float GetDebuffDuration() const { return DebuffDuration; }  // ep. 308
	float GetDebuffFrequency() const { return DebuffFrequency; }  // ep. 308
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }  // ep. 308
	FVector GetDeathImpulse() const { return DeathImpulse; } // ep. 313
	FVector GetKnockbackForce() const { return KnockbackForce; } // ep. 315


	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }  // ep. 308
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }  // ep. 308
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }  // ep. 308
	void SetDebuffFrequency(float InFrequency) { DebuffFrequency = InFrequency; }   // ep. 308
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; } // ep. 309
	void SetDeathImpulse(FVector InImpulse) { DeathImpulse = InImpulse; } // ep. 313
	void SetKnockbackForce(FVector InForce) { KnockbackForce = InForce; } // ep. 315

	// ** Returns the actual struct used for serialization, subclasses must override this! */

	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	// ** Creates a copy of this context, used to duplicate for later modifications */

	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult()) 
		{
			// ** Does a deep copy of the hit result */

			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	// ** Custom serialization, subclasses must override this */

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);



protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false; // ep. 308

	UPROPERTY()
	float DebuffDamage = 0.f; // ep. 308

	UPROPERTY()
	float DebuffDuration = 0.f; // ep. 308

	UPROPERTY()
	float DebuffFrequency = 0.f; // ep. 308

	TSharedPtr<FGameplayTag> DamageType; // ep. 308

	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector; // ep. 313

	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector; // ep. 315
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};


