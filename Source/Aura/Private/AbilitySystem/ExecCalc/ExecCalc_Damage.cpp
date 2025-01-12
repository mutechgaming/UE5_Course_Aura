// Copyrighte Steven Mutek

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAbilityTypes.h"
#include "AuraGameplayTags.h" 
#include "Kismet/GameplayStatics.h"
#include "Interaction/CombatInterface.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResilience);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResilience, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResilienceDef);

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef); 
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef); 
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef); 
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef); 

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;
	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
	TagsToCaptureDef.Add(Tags.Attribute_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDef.Add(Tags.Attribute_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDef.Add(Tags.Attribute_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDef.Add(Tags.Attribute_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);
	TagsToCaptureDef.Add(Tags.Attribute_Secondary_CriticalHitResilience, DamageStatics().CriticalHitResilienceDef);

	TagsToCaptureDef.Add(Tags.Attribute_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCaptureDef.Add(Tags.Attribute_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	TagsToCaptureDef.Add(Tags.Attribute_Resistance_Arcane, DamageStatics().ArcaneResistanceDef);
	TagsToCaptureDef.Add(Tags.Attribute_Resistance_Physical, DamageStatics().PhysicalResistanceDef);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent(); 

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Debuff

	DetermineDebuff(Spec, ExecutionParams, EvaluationParameters, TagsToCaptureDef);

	// Get damage set by caller magnitude

	float Damage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag> Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		
		checkf(TagsToCaptureDef.Contains(ResistanceTag), TEXT("TagsToCaptureDef doesnt contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDef[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		if (DamageTypeValue <= 0.f)
		{
			continue;
		}

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		if (UAuraAbilitySystemLibrary::IsRadialDamage(EffectContextHandle))
		{
			// 1. override TakeDamage() in AuraCharacterBase
			// 2. create delegates OnDamageDelegate and broadcast damage received in TakeDamage()
			// 3. bind lambda to OnDamageDelegate on the victim here
			// 4. call UGameplayStatics::RadialDamageWithFalloff to cause damage (this will result in TakeDamage being called on the victim which will then broadcast OnDamageDelegate
			// 5. in lambda, set damage type value to the damaged received from broadcast

			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(TargetAvatar))
			{
				CombatInterface->GetOnDamageSignature().AddLambda(
					[&](float DamageAmount)
					{
						DamageTypeValue = DamageAmount;
					});
			}

			UGameplayStatics::ApplyRadialDamageWithFalloff(TargetAvatar,
				DamageTypeValue,
				0.f,
				UAuraAbilitySystemLibrary::GetRadialDamageOrigin(EffectContextHandle),
				UAuraAbilitySystemLibrary::GetRadialDamageInnerRadius(EffectContextHandle),
				UAuraAbilitySystemLibrary::GetRadialDamageOuterRadius(EffectContextHandle),
				1.f,
				UDamageType::StaticClass(),
				TArray<AActor*>(),
				SourceAvatar,
				nullptr);
		}

		Damage += DamageTypeValue;
	}

	// If block, halve damage

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	Damage = bBlocked ? Damage * 0.5f : Damage;
	
	// Armor penetration ignores a percentage of target armor

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f); 

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel); 
	 
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel); 

	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	// Critical hit data (chance, damage, resilience)

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	// Critical Hit Resilience

	float TargetCriticalHitResilience = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResilienceDef, EvaluationParameters, TargetCriticalHitResilience);
	TargetCriticalHitResilience = FMath::Max<float>(TargetCriticalHitResilience, 0.f);

	FRealCurve* CriticalHitResilienceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResilience"), FString());
	const float CriticalHitResilienceCoefficient = CriticalHitResilienceCurve->Eval(TargetPlayerLevel);

	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResilience * CriticalHitResilienceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	Damage = bCriticalHit ? ((Damage * 2.f) + SourceCriticalHitDamage) : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectSpec& Spec, const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters& EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		FGameplayTag DamageType = Pair.Key;
		FGameplayTag DebuffType = Pair.Value;
		float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > -0.5f) // .5 Padding for floating point imprecision
		{
			// Determine if there was a successful debuff
			float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);
			float TargetDebuffResistance = 0.f;
			FGameplayTag ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);

			}
		}
	}
}
