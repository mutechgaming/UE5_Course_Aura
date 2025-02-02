// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"


// can use struct to forward declare specific items

class UInputMappingContext;
class AMagicCircle; 
class UInputAction;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class UDamageTextComponent;
class USplineComponent;
class IEnemyInterface;
class IHighlightInterface;
struct FInputActionValue; 


enum class ETargetingStatus : uint8
{
	TargetingEnemy,
	TargetingNonEnemy,
	NotTargeting
};


UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable) // when client or being replicated, need to add implementations to the cpp definition
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bIsBlockedHit, bool bIsCriticalHit);

	UFUNCTION(BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial);

	UFUNCTION(BlueprintCallable)
	void HideMagicCircle();

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(Editanywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(Editanywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(Editanywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false; 
	
	void Move(const FInputActionValue &InputActionValue);

	void CursorTrace();
	TObjectPtr<AActor> LastActor; 
	TObjectPtr<AActor> ThisActor;
	FHitResult CursorHit;

	void HighlightActor(AActor* InActor);
	void UnHighlightActor(AActor* InActor);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC(); 

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f; 
	float ShortPressedThreshold = 0.5f;
	bool bAutoRunning = false;
	ETargetingStatus TargetingStatus = ETargetingStatus::NotTargeting;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UNiagaraSystem> ClickNiagaraSystem;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMagicCircle> MagicCircleClass; // ep. 346

	UPROPERTY() 
	TObjectPtr<AMagicCircle> MagicCircle; // ep. 346


	void UpdateMagicCircleLocation();
};
