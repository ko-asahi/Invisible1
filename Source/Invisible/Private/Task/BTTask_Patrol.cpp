// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_Patrol.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Enemy/PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = TEXT("Patrol To Next Point");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if(!AIController) return EBTNodeResult::Failed;

    AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
    if(!Enemy || !Enemy->AssignedPatrolPath || Enemy->AssignedPatrolPath->Num() == 0)
        return EBTNodeResult::Failed;

    AActor* TargetPoint = Enemy->GetNextPatrolPoint();
    if(!TargetPoint) return EBTNodeResult::Failed;

    // 记录本次到达的索引，供回调中读取行为数据
    int32 ArrivedIndex = Enemy->CurrentPatrolPointIndex;

    // 更新下一个索引(已废弃，为了配合编辑模式路径点)
    //Enemy->CurrentPatrolPointIndex = (Enemy->CurrentPatrolPointIndex + 1) % Enemy->AssignedPatrolPath->Num();


    FBTTask_PatrolMemory* Memory = reinterpret_cast<FBTTask_PatrolMemory*>(NodeMemory);

    // 绑定移动完成回调
    // ReceiveMoveCompleted 是动态多播委托，不支持 AddLambda
    // 改用 PathFollowingComponent::OnRequestFinished（普通多播委托）
    Memory->MoveCompletedHandle = AIController->GetPathFollowingComponent()->OnRequestFinished.AddLambda(
        [this, &OwnerComp, Memory, ArrivedIndex](FAIRequestID RequestID, const FPathFollowingResult& Result)
        {
            AEnemyAIController* Controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

            if (Controller && Controller->GetPathFollowingComponent())
                Controller->GetPathFollowingComponent()->OnRequestFinished.Remove(Memory->MoveCompletedHandle);

            if (Result.Code == EPathFollowingResult::Success)
            {
                // 读取该路径点的行为数据并写入 Blackboard
                AEnemyBase* Pawn = Cast<AEnemyBase>(Controller ? Controller->GetPawn() : nullptr);
                UBlackboardComponent* BB = Controller ? Controller->GetBlackboardComponent() : nullptr;

                // 为了配合编辑模式路径点，将路径点自增由原有的提前自增改为在此处自增
                if (Pawn && Pawn->AssignedPatrolPath && Pawn->AssignedPatrolPath->Num() > 0)
                {
                    Pawn->CurrentPatrolPointIndex =
                        (ArrivedIndex + 1) % Pawn->AssignedPatrolPath->Num();
                }

                if (Pawn && Pawn->AssignedPatrolPath && BB)
                {
                    FPatrolWaypointData Data = Pawn->AssignedPatrolPath->GetWaypointData(ArrivedIndex);

                    BB->SetValueAsEnum(TEXT("WaypointBehavior"), (uint8)Data.Behavior);
                    BB->SetValueAsFloat(TEXT("WaypointWaitTime"), Data.WaitTime);
                    BB->SetValueAsFloat(TEXT("LookAngle"), Data.LookAngle);
                    BB->SetValueAsFloat(TEXT("LookSpeed"), Data.LookSpeed);
                    BB->SetValueAsFloat(TEXT("PreLookPauseTime"), Data.PreLookPauseTime);

                    // 若使用自定义中轴线，则设置 Point 和 LookCenterYawOffset
                    float CenterYaw = Pawn->GetActorRotation().Yaw;
                    if(Data.bUseCustomLookCenter)
                    {
                        if(IsValid(Data.Point))
                        {
                            // const FVector ToCenter = (Data.LookCenterActor->GetActorLocation() - Pawn->GetActorLocation()).GetSafeNormal2D();

                            // if(!ToCenter.IsNearlyZero())
                            // {
                            //     CenterYaw = ToCenter.Rotation().Yaw;
                            // }
                            CenterYaw = Data.Point->GetActorRotation().Yaw;
                        }

                        CenterYaw = FRotator::NormalizeAxis(CenterYaw + Data.LookCenterYawOffset);
                    }

                    BB->SetValueAsBool(TEXT("UseLookCenterYaw"), Data.bUseCustomLookCenter);
                    BB->SetValueAsFloat(TEXT("LookCenterYaw"), CenterYaw);
                }
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            }
            else
            {
                FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
            }
        });

    // 发起移动
    FAIMoveRequest MoveRequest;
    MoveRequest.SetGoalActor(TargetPoint);
    MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
    MoveRequest.SetCanStrafe(false);

    // 状态恢复，让后续 MoveTo 阶段可边走边转（含避障）
    if (Enemy && Enemy->GetCharacterMovement())
    {
        Enemy->GetCharacterMovement()->bOrientRotationToMovement = true;
    }

    AIController->MoveTo(MoveRequest);

    // 返回 InProgress，告知行为树正在执行
    return EBTNodeResult::InProgress;
}


void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (BB && BB->GetValueAsBool(AEnemyAIController::BB_HasInterest))
    {
        // 巡逻中检测到兴趣点，立刻完成任务（Failed 会使 Selector 继续尝试下一分支）
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
}


void UBTTask_Patrol::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    FBTTask_PatrolMemory* Memory = reinterpret_cast<FBTTask_PatrolMemory*>(NodeMemory);
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

    // 先解绑回调，防止后续 StopMovement 触发 OnRequestFinished 导致二次 FinishLatentTask
    if (AIController && AIController->GetPathFollowingComponent() && Memory->MoveCompletedHandle.IsValid())
    {
        AIController->GetPathFollowingComponent()->OnRequestFinished.Remove(Memory->MoveCompletedHandle);
        Memory->MoveCompletedHandle.Reset();
    }

    // 非正常完成（中止或失败）时立刻停止移动
    if (AIController && TaskResult != EBTNodeResult::Succeeded)
    {
        AIController->StopMovement();
        if (APawn* Pawn = AIController->GetPawn())
        {
            if (UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
            {
                MoveComp->StopMovementImmediately();
            }
        }
    }
}


uint16 UBTTask_Patrol::GetInstanceMemorySize() const
{
    return sizeof(FBTTask_PatrolMemory);
}