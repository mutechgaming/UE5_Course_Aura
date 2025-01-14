// Copyright Steven Mutek


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	float ManaCost = FMath::Abs(GetManaCost(Level));
	float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>ARCANE SHARDS: </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"

			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"

			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Summon shards of arcane energy, causing: </>"

			//Damage
			"<Damage>%d</><Default> radial arcane damage and knocking back enemies </>\n\n"),

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
			"<Default>Summon %d shards of arcane energy, causing: </>"

			//Damage
			"<Damage>%d</><Default> arcane damage and knocking back enemies</>\n\n"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShards),
			ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
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
		"<Default>Summon %d shards of arcane energy, causing: </>"

		//Damage
		"<Damage>%d</><Default> arcane damage and knocking back enemies</>\n\n"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShards),
		ScaledDamage);
}
