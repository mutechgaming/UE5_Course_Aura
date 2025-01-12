// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// ** Primary Attributes ** //
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;

	// ** Secondary Attributes ** //
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResilience;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;

	// ** Vital Attributes ** //
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;

	// ** Meta Attributes **//
	FGameplayTag Attribute_Meta_IncomingXP;

	// ** Input Tags ** //
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	// ** Combat & Meta Tags ** //
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	FGameplayTag Effects_HitReact;

	// ** Resistances ** //
	FGameplayTag Attribute_Resistance_Fire;
	FGameplayTag Attribute_Resistance_Lightning;
	FGameplayTag Attribute_Resistance_Arcane;
	FGameplayTag Attribute_Resistance_Physical;

	// ** Abilities ** //
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Lightning_Electrocute;
	FGameplayTag Abilities_Arcane_ArcaneShards;

	FGameplayTag Abilities_None;

	FGameplayTag Abilities_HitReact;
	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Elligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;

	//** Passive Spells**//
	FGameplayTag Abilities_Passive_HaloOfProtection;
	FGameplayTag Abilities_Passive_LifeSiphon;
	FGameplayTag Abilities_Passive_ManaSiphon;



	// ** Debuffs ** //  // ep. 303
	FGameplayTag Debuff_Burn; 
	FGameplayTag Debuff_Stun;  
	FGameplayTag Debuff_Arcane;  
	FGameplayTag Debuff_Physical;  

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	// ** Cooldowns ** //
	FGameplayTag Cooldown_Fire_FireBolt;

	// ** Combat Sockets ** //
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_Tail;

	//** Montages **//
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	//** Player Tags **//
	FGameplayTag Player_Block_InputPressed; // ep. 323
	FGameplayTag Player_Block_InputHeld; // ep. 323
	FGameplayTag Player_Block_InputReleased; // ep. 323
	FGameplayTag Player_Block_CursorTrace; // ep. 323



	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;


protected:


private:
	static FAuraGameplayTags GameplayTags;

};