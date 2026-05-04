#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GameOverShotFinished.generated.h"

/**
 * 游戏结束开火动画结束通知
 */

UCLASS()
class INVISIBLE_API UAnimNotify_GameOverShotFinished : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 通知函数
	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};