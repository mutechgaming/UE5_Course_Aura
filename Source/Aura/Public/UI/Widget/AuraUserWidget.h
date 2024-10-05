// Copyrighte Steven Mutek

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

// The idea is to make these controllers & widgets modular so that multiple widgets and controllers can be swapped out without messing with hard coded classes.
// Goal is to make a one way connection from widgets to the controller -> widget knows what controller to go too but the controller doesnt know what widgets are coming to it.

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly) // read it but now edit it in blueprint
		TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

};
