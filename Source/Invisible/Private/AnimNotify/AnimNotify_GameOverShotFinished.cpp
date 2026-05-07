#include "AnimNotify/AnimNotify_GameOverShotFinished.h"
#include "Invisible_GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// 通知函数
void UAnimNotify_GameOverShotFinished::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
     
	if (!MeshComp)
	{
		return;
	}

	if (AInvisible_GameModeBase* GM = Cast<AInvisible_GameModeBase>(UGameplayStatics::GetGameMode(MeshComp)))
	{
		GM->FinishGameOverSequence();
	}
}