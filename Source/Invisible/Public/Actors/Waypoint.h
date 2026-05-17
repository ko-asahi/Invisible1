#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS(Blueprintable)
class INVISIBLE_API AWaypoint : public AActor
{
	GENERATED_BODY()

public:
	AWaypoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	TObjectPtr<AWaypoint> NextWaypoint = nullptr;
};
