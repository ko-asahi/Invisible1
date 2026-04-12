#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "TraitTargetInterface.generated.h"


/**
 * TraitTargetInterface是一个特质目标接口，用于获取特质目标所包含的 Tag
 */

UINTERFACE(BlueprintType)
class UTraitTargetInterface : public UInterface
{
    GENERATED_BODY()
};

class INVISIBLE_API ITraitTargetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Trait")
    FGameplayTagContainer GetInteractionTargetTags() const;
};