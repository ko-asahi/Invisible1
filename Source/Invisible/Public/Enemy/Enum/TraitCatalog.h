#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "TraitCatalog.generated.h"

/**
 * TraitCatalog是一个特质目录，包含了特质的属性定义
 */

UCLASS(BlueprintType)
class INVISIBLE_API UTraitCatalog : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<TObjectPtr<UTraitDefinition>> TraitDefinitions;
};