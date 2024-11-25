// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// virtual void functions with = 0 becomes a "pure" virtual function and abstract and does not need to be defined in the parent class. --
// -- It will be overriden in each other class that inherits this class. Pure virutal functions must be overriden by inherited class or errors will occur


UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()


public:
	virtual void HighlightActor() = 0; 
	virtual void UnHighlightActor() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetCombatTarget() const;
};
