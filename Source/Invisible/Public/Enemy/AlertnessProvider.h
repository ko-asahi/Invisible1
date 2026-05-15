#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AlertnessProvider.generated.h"

UINTERFACE(BlueprintType)
class INVISIBLE_API UAlertnessProvider : public UInterface
{
    GENERATED_BODY()
};

class INVISIBLE_API IAlertnessProvider
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI|Perception|Alert")
    float GetAlertness() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI|Perception|Alert")
    float GetAlertnessNormalized() const;
};
