
#pragma once
#include "CoreMinimal.h"
#include "WaypointTypes.generated.h"

// 巡逻点行为类型
UENUM(BlueprintType)
enum class EWaypointBehavior : uint8
{
    None        UMETA(DisplayName = "直接经过"),
    LookAround  UMETA(DisplayName = "停下扫视"),
    Wait        UMETA(DisplayName = "原地等待"),
};