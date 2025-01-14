// Copyright Steven Mutek


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>ELECTROCUTE: </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"

			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"

			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Emits a beam of lighting to shock enemies overtime,: </>"

			//Damage
			"<Damage>%d</><Default> causing lightning damage with a chance to stun </>\n\n"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>ELECTROCUTE</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"

			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"

			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Emits a beam of lighting, propagating to %d additional targets nearby, causing: </>"

			//Damage
			"<Damage>%d</><Default> lightning damage with a chance to stun</>\n\n"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		//Title
		"<Title>NEXT LEVEL</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"

		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"

		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Emits a beam of lighting, propagating to %d additional targets nearby, causing : </>"

		//Damage
		"<Damage>%d</><Default> lightning damage with a chance to stun</>\n\n"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShockTargets),
		ScaledDamage);
}
