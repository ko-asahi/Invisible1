#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InvisibleWidgetHelper.generated.h"

class UUserWidget;

UCLASS()
class INVISIBLE_API UInvisibleWidgetHelper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "UI|Alertness")
    static float GetAlertnessFromObject(const UObject* Object);

    UFUNCTION(BlueprintPure, Category = "UI|Alertness")
    static float GetAlertnessNormalizedFromObject(const UObject* Object);

    UFUNCTION(BlueprintPure, Category = "UI|Alertness")
    static float GetAlertnessFromWidgetOwner(const UUserWidget* Widget);

    UFUNCTION(BlueprintPure, Category = "UI|Alertness")
    static float GetAlertnessNormalizedFromWidgetOwner(const UUserWidget* Widget);
};
