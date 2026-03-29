// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_LookAround.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LookAround::UBTTask_LookAround()
{
    NodeName = TEXT("Look Around");
    bNotifyTick = true; // 启用 TickTask
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
    
    UBlackboardComponent* BB = AIController->GetBlackboardComponent();
    // 获取初始朝向
    FBTTask_LookAroundMemory* Memory = reinterpret_cast<FBTTask_LookAroundMemory*>(NodeMemory);
    Memory->InitialYaw = AIController->GetPawn()->GetActorRotation().Yaw;
    Memory->Phase = 0;
    Memory->WaitBeforeSweepRemaining = FMath::Max(BB ? BB->GetValueAsFloat(TEXT("PreLookPauseTime")) : 0.0f,0.0f);

    // 旧逻辑，以当前朝向作为中轴线
    // // 从黑板获取目标朝向
    // UBlackboardComponent* BB = AIController->GetBlackboardComponent();
    // float LookAngle = BB ? BB->GetValueAsFloat(TEXT("LookAngle")) : 60.0f;

    // // 先左转（角度归一化，防止角度错误）
    // Memory->TargetYaw = FRotator::NormalizeAxis(Memory->InitialYaw - LookAngle);

    // // 返回 InProgress，告知行为树正在执行
    // return EBTNodeResult::InProgress;

    // 新逻辑，使用中轴线朝向，先转到中轴线
    
    const bool bUseCenter = BB ? BB->GetValueAsBool(TEXT("UseLookCenterYaw")) : false;
    const float CenterYawFromBB = BB ? BB->GetValueAsFloat(TEXT("LookCenterYaw")) : Memory->InitialYaw;

    // 启用中轴线时，使用中轴线朝向，否则使用初始朝向
    Memory->CenterYaw = bUseCenter ? FRotator::NormalizeAxis(CenterYawFromBB) : FRotator::NormalizeAxis(Memory->InitialYaw);

    Memory->TargetYaw = Memory->CenterYaw;

    return EBTNodeResult::InProgress;

}

// 每帧更新转向
void UBTTask_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(!AIController || !AIController->GetPawn())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // 获取黑板中的转向数据
    UBlackboardComponent* BB = AIController->GetBlackboardComponent();

    // if (BB && BB->GetValueAsObject(TEXT("VisualTargetActor")) != nullptr)
    // {
    //     // 发现玩家，提前结束扫视，行为树会切换到打探分支
    //     FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    //     return;
    // }

    if (BB)
    {
        // const bool bHasVisualTarget = (BB->GetValueAsObject(TEXT("VisualTargetActor")) != nullptr);
        // const bool bCanInterrupt = BB->GetValueAsBool(TEXT("IsSuspicious")) || BB->GetValueAsBool(TEXT("IsChasing"));
        const bool bHasInterest = BB->GetValueAsBool(TEXT("HasInterest"));
        if (bHasInterest)
        {
            // 发现玩家，提前结束扫视
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return;
        }
    }

    float LookAngle = BB ? BB->GetValueAsFloat(TEXT("LookAngle")) : 60.0f;
    float LookSpeed = BB ? BB->GetValueAsFloat(TEXT("LookSpeed")) : 80.0f;

    FBTTask_LookAroundMemory* Memory = reinterpret_cast<FBTTask_LookAroundMemory*>(NodeMemory);
    APawn* Pawn = AIController->GetPawn();

    float CurrentYaw = Pawn->GetActorRotation().Yaw; // 当前朝向
    const float TargetYaw = FRotator::NormalizeAxis(Memory->TargetYaw);

    float NewYaw = FMath::FixedTurn(CurrentYaw, TargetYaw, LookSpeed * DeltaSeconds);
    Pawn->SetActorRotation(FRotator(0.0f, NewYaw, 0.0f));

    // 检查是否到达目标朝向（中轴线朝向或初始朝向）
    const float YawDelta = FMath::Abs(FMath::FindDeltaAngleDegrees(NewYaw, TargetYaw));

    // 如果在静止状态
    if (Memory->Phase == 1)
    {
        Memory->WaitBeforeSweepRemaining -= DeltaSeconds;
        if (Memory->WaitBeforeSweepRemaining <= 0.0f)
        {
            Memory->TargetYaw = FRotator::NormalizeAxis(Memory->CenterYaw - LookAngle);
            Memory->Phase = 2;
        }
        return;
    }

    if (YawDelta < 1.0f)
    {
        //Memory->Phase++;
        switch(Memory->Phase)
        {
            case 0: // 到中轴
            if (Memory->WaitBeforeSweepRemaining > KINDA_SMALL_NUMBER)
            {
                Memory->Phase = 1; // 先静止
            }
            else
            {
                Memory->TargetYaw = FRotator::NormalizeAxis(Memory->CenterYaw - LookAngle);
                Memory->Phase = 2;
            }
                break;
            case 2: // 左 -> 右
                Memory->TargetYaw = FRotator::NormalizeAxis(Memory->CenterYaw + LookAngle);
                Memory->Phase = 3;
                break;
            case 3: // 右 -> 回中轴
                Memory->TargetYaw = FRotator::NormalizeAxis(Memory->CenterYaw);
                Memory->Phase = 4;
                break;
            case 4:
            default:
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                break;
        }
    }
}

uint16 UBTTask_LookAround::GetInstanceMemorySize() const
{
    return sizeof(FBTTask_LookAroundMemory);
}