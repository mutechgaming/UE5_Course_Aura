// Copyright Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDebuffNiagaraComponent : public UNiagaraComponent // ep. 311
{
	GENERATED_BODY()
	
public:
	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
	FGameplayTag DebuffTag;

protected:

	virtual void BeginPlay() override;
	void DebuffTagChanged(FGameplayTag CallbackTag, int32 NewCount);
};
