// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SIZZ_CustomIndicatorRefreshValue.generated.h"


UCLASS()
class SIZZ_SPELL_INDICATOR_API USIZZ_CustomIndicatorRefreshValue : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,Category ="Indicator",meta=(ClampMin=0,UIMin=0,ClampMax =1,UIMax=1))
	float RefreshValue{0.02};
};
