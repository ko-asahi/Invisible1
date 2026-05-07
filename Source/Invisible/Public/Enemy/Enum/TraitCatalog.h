#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "TraitCatalog.generated.h"

/**
 * TraitCatalog是一个特质目录，包含了特质的属性定义（用于创建数据资产，并写入特质配置文件，此时特质参数被写入行为系统）
 */

UCLASS(BlueprintType)
class INVISIBLE_API UTraitCatalog : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<TObjectPtr<UTraitDefinition>> TraitDefinitions;
};