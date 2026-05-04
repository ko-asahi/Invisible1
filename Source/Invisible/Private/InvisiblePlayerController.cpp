// Fill out your copyright notice in the Description page of Project Settings.
#include "InvisiblePlayerController.h"
#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "Enemy/Trait/TraitSubsystem.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "Enemy/Trait/TraitActionResolver.h"
#include "Enemy/Trait/TraitActionProfile.h"
#include "Enemy/Interface/TraitTargetInterface.h"
#include "Interaction/InteractionTargetComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIInteractionDebug, Log, All);


void AInvisiblePlayerController::BeginPlay()
{
    Super::BeginPlay();

    UpdateInputContext();

    // 初始化当前能量
    CurrentPathEnergy = MaxPathEnergy;
    DisplayPathEnergy = CurrentPathEnergy;
    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy, 0.f, MaxPathEnergy);

    // 初始化信息面板
    if(AIInfoPanelClass)
    {
        AIInfoPanelInstance = CreateWidget<UAIInfoPanelWidget>(this, AIInfoPanelClass);
        if(AIInfoPanelInstance)
        {
            AIInfoPanelInstance->AddToViewport(10);
            AIInfoPanelInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    // 注册ai交互委托
    RegisterEnemyInteractionDelegates();

    // 注册ai事件结束委托
    RegisterEnemyInteractionResolvedDelegates();
}

void AInvisiblePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!bIsEditMode || !EditCamera)
    {
        bEditRotateHeld = false;
        TickEnergyRegen(DeltaTime);
        return;
    }

    // 使用真实帧时间，不受 GlobalTimeDilation 影响
    const float RealDeltaTime = FApp::GetDeltaTime();

    // 将当前帧的平移输入应用于相机
    if(!EditPanInput.IsNearlyZero())
    {
        EditCamera->PanCamera(EditPanInput, RealDeltaTime);
    }

    

    // 每帧更新鼠标投影
    EditCamera->UpdateGroundRing(this);


    // 绘制路径预览
    if(bPathDragActive && bHasPreviewPath)
    {
        DrawPathPoints(PreviewPathPoints, FColor::Blue); // 拖拽中的路径
    }

    for (const FLockedAIPath& Path : LockedAIPaths)
    {
        if (Path.OwnerPawn.IsValid() && Path.Points.Num() >= 2)
        {
            DrawPathPoints(Path.Points, FColor::Yellow);
        }
    }
    
}

void AInvisiblePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // 切换输入模式按键绑定
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if(!EnhancedInputComponent)
    {
        UE_LOG(LogTemp, Log, TEXT("增强输入组件为空"));
        return;
    }

    // =====切换模式按键绑定=====
    if(EnhancedInputComponent)
    {
        if(SwitchModeAction && SwitchModeMappingContext)
        {
            EnhancedInputComponent->BindAction(SwitchModeAction, ETriggerEvent::Started, this, &AInvisiblePlayerController::SwitchMode);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("SwitchModeAction或SwitchModeMappingContext为null"));
        }
    }

    // =====跟随模式=====
    // 移动输入
    if(MoveAction)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnMove);
    }
    
    // 旋转输入
    if(RotateAction)
    {
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnRotate);
    }

    // 旋转状态按键
    if(RotateHoldAction)
    {
        EnhancedInputComponent->BindAction(RotateHoldAction, ETriggerEvent::Started,   this, &AInvisiblePlayerController::OnRotateHoldStarted);
        EnhancedInputComponent->BindAction(RotateHoldAction, ETriggerEvent::Completed, this, &AInvisiblePlayerController::OnRotateHoldCompleted);
    }

    // 蹲下输入按键
    if(CrouchAction)
    {
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AInvisiblePlayerController::OnCrouchToggle);
    }


    // =====编辑模式=====
    // 移动输入
    if(EditPanAction)
    {
        EnhancedInputComponent->BindAction(EditPanAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnEditPan);
        EnhancedInputComponent->BindAction(EditPanAction, ETriggerEvent::Completed, this, &AInvisiblePlayerController::OnEditPanCompleted);
    }

    // 旋转输入
    if(EditRotateAction)
    {
        EnhancedInputComponent->BindAction(EditRotateAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnEditRotate);
    }

    // 旋转状态按键
    if(EditRotateHoldAction)
    {
        EnhancedInputComponent->BindAction(EditRotateHoldAction, ETriggerEvent::Started,   this, &AInvisiblePlayerController::OnEditRotateHoldStarted);
        EnhancedInputComponent->BindAction(EditRotateHoldAction, ETriggerEvent::Completed, this, &AInvisiblePlayerController::OnEditRotateHoldCompleted);
        // EnhancedInputComponent->BindAction(EditRotateHoldAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnEditRotateHold);
    }

    // 单位选择按键
    if(EditSelectAction)
    {
        EnhancedInputComponent->BindAction(EditSelectAction, ETriggerEvent::Started,   this, &AInvisiblePlayerController::OnStartPathDrag);
        EnhancedInputComponent->BindAction(EditSelectAction, ETriggerEvent::Triggered, this, &AInvisiblePlayerController::OnEditPathDragTriggered);
        EnhancedInputComponent->BindAction(EditSelectAction, ETriggerEvent::Completed, this, &AInvisiblePlayerController::OnEditPathDragCompleted);
    }

    // 奔跑输入按键
    if (RunAction)
    {
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started,   this, &AInvisiblePlayerController::OnRunStarted);
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AInvisiblePlayerController::OnRunCompleted);
    }

    // 删除已锁定路径按键
    if(EditRemovePathAction)
    {
        EnhancedInputComponent->BindAction(EditRemovePathAction, ETriggerEvent::Started, this, &AInvisiblePlayerController::OnRemoveSelectedAIPath);
    }
}


// =====切换模式=====
void AInvisiblePlayerController::SwitchMode()
{
    if (bGameplayInputLocked) return;

    bIsEditMode = !bIsEditMode;

    // 进入编辑模式
    if(bIsEditMode)
    {
        // 获取当前玩家相机位置与朝向
        FVector  CamLoc;
        FRotator CamRot;
        GetPlayerViewPoint(CamLoc, CamRot);

        // 生成之前先判断类是否已在蓝图中设置
        if(!EditModeCameraClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("EditModeCameraClass 未设置，请在蓝图中指定"));
            
            return;
        }
        // EditCamera = GetWorld()->SpawnActor<AEditModeCamera>(EditModeCameraClass, CamLoc, FRotator::ZeroRotator);


        // if(EditCamera)
        // {
        //     // 初始化相机位置与朝向(朝向由EditModeCamera内参数CameraPitch控制)
        //     EditCamera->InitializeCamera(CamLoc, CamRot.Yaw);

        //     // 平滑过渡到当前视角
        //     //SetViewTargetWithBlend(EditCamera,EditModeCameraTransitionSpeed);

        //     // 立即切换视角
        //     SetViewTarget(EditCamera);
        // }

        // 用玩家位置作为编辑相机初始圆心（不再用旧相机位置）
        const FVector PivotSpawnLoc = GetPawn() ? GetPawn()->GetActorLocation() : CamLoc;
        EditCamera = GetWorld()->SpawnActor<AEditModeCamera>(EditModeCameraClass, PivotSpawnLoc, FRotator::ZeroRotator);
        if (EditCamera)
        {
            // 只同步当前视角Yaw，位置由Spawn位置 + 蓝图里组件参数决定
            EditCamera->InitializeCamera(CamRot.Yaw);
            SetViewTarget(EditCamera);
        }

        // 进入编辑模式时，暂停玩家和所有敌人
        TArray<AActor*> FoundPawns;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundPawns);
        for (AActor* A : FoundPawns) { A->CustomTimeDilation = 0.f; }
        
        // 敌人父类
        TArray<AActor*> FoundEnemies;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);
        for (AActor* A : FoundEnemies) {
            if(!A) continue;
            A->CustomTimeDilation = 0.f;
            
            if(APawn* EnemyPawn = Cast<APawn>(A))
            {
                if(AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(EnemyPawn->GetController()))
                {
                    EnemyAI->SetAIPaused(true);
                }
            }
        }

        // 显示鼠标
        bShowMouseCursor = true;
        //SetInputMode(FInputModeGameOnly());
        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);  // 光标锁定在视口内
        InputMode.SetHideCursorDuringCapture(false);  // 按住时不隐藏光标
        SetInputMode(InputMode);

        // 暂停能量回复
        StopEnergyRegen();

        // 隐藏所有ai头顶交互按钮
        HideAllInteractionButtons();

        UE_LOG(LogTemp, Log, TEXT("切换为编辑模式"));
    }

    // 退出编辑模式
    if(!bIsEditMode)
    {
        // 隐藏所有ai头顶交互按钮
        HideAllInteractionButtons();

        // 退出编辑模式时，恢复
        TArray<AActor*> FoundPawns;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundPawns);
        for (AActor* A : FoundPawns)   { A->CustomTimeDilation = 1.f; }

        TArray<AActor*> FoundEnemies;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);
        for (AActor* A : FoundEnemies) { 
            if(!A) continue;
            A->CustomTimeDilation = 1.f;
            
            if(APawn* EnemyPawn = Cast<APawn>(A))
            {
                if(AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(EnemyPawn->GetController()))
                {

                    // 将锁定路径设置给AI
                    const int32 LockedIndex = FindLockedPathIndexByPawn(EnemyPawn);
                    if (LockedIndex != INDEX_NONE && LockedAIPaths[LockedIndex].Points.Num() >= 2)
                    {
                        const FLockedAIPath& LockedPath = LockedAIPaths[LockedIndex];

                        EnemyAI->SetInjectedPath(LockedPath.Points);

                        // 在写入互动前检验相关行为数据
                        const bool bActionDataValid = 
                            LockedPath.TargetActor.IsValid() &&
                            LockedPath.ConfirmedActionTag.IsValid() &&
                            LockedPath.ConfirmedDuration >= 0.0f &&
                            LockedPath.ConfirmedExecutionRadius >= 0.0f;

                        if(!bActionDataValid)
                        {
                            UE_LOG(LogTemp, Warning, TEXT("[Interaction] 跳过行为写入 Pawn = %s"),*GetNameSafe(EnemyPawn));
                            EnemyAI->ClearPendingInteraction();
                        }

                        // 注入“已确认互动”
                        else if (LockedPath.bIsInteractionPath && LockedPath.bActionConfirmed)
                        {
                            AActor* TargetActor = LockedPath.TargetActor.Get();
                            // EnemyAI->SetPendingInteraction(
                            //     TargetActor,
                            //     LockedPath.ConfirmedActionTag,
                            //     LockedPath.ConfirmedDuration,
                            //     LockedPath.ConfirmedExecutionRadius
                            // );
                            // 新：通过 FTraitInteractionContext 实现
                            FTraitInteractionContext Ctx;
                            Ctx.SourceActor = EnemyPawn;
                            Ctx.TargetActor = LockedPath.TargetActor.Get();
                            Ctx.InteractionType = Cast<AEnemyBase>(Ctx.TargetActor.Get())
                                ? ETraitInteractionType::AI_With_AI
                                : ETraitInteractionType::AI_With_Object;
                            Ctx.Spec.ActionTag = LockedPath.ConfirmedActionTag;
                            Ctx.Spec.Duration = LockedPath.ConfirmedDuration;
                            Ctx.Spec.ExecutionRadius = LockedPath.ConfirmedExecutionRadius;
                            Ctx.Spec.EnergyCost = LockedPath.ConfirmedActionCost;
                            EnemyAI->SetPendingInteractionContext(Ctx);

                            // 获取源AI和目标AI预计交互点（源AI的路径终点）
                            if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(Ctx.TargetActor.Get()))
                            {
                                // 目标AI不是源AI时，再设置外部等待锁
                                if(TargetEnemy != EnemyPawn)
                                {
                                    if (AEnemyAIController* TargetCtrl = Cast<AEnemyAIController>(TargetEnemy->GetController()))
                                    {
                                        // 预计互动点
                                        FVector ExpectedInteractionPoint = EnemyPawn->GetActorLocation();
                                        if (!BuildExpectedInteractionPointForTargetHold(LockedPath, EnemyPawn, TargetEnemy, ExpectedInteractionPoint))
                                        {
                                            ExpectedInteractionPoint = EnemyPawn->GetActorLocation();
                                        }
                                        TargetCtrl->SetExternalApproachHoldByLocation(ExpectedInteractionPoint);
                                    }
                                }
                            }

                        }
                        else
                        {
                            EnemyAI->ClearPendingInteraction();
                        }
                    }
                    else
                    {
                        // 没有锁定路径也清掉，避免上一次残留
                        EnemyAI->ClearPendingInteraction();
                    }

                    EnemyAI->StartDetectionTimer();
                    EnemyAI->SetAIPaused(false);
                }
            }
        }

        // 平滑过渡回跟随视角
        //SetViewTargetWithBlend(EditCamera,EditModeCameraTransitionSpeed);

        // 销毁编辑模式相机(延迟销毁)
        // if(EditCamera)
        // {
        //     AEditModeCamera* CameraToDestroy = EditCamera;
        //     EditCamera = nullptr;
        //     FTimerHandle DestroyHandle;
        //     GetWorldTimerManager().SetTimer(DestroyHandle, [CameraToDestroy]()
        //     {
        //         if(IsValid(CameraToDestroy))
        //             CameraToDestroy->Destroy();
        //     }, EditModeCameraTransitionSpeed + 0.1f, false);
        // }

        // 立即切回跟随视角并销毁编辑相机
        SetViewTarget(GetPawn());
        if(EditCamera)
        {
            EditCamera->Destroy();
            EditCamera = nullptr;
        }


        // 隐藏鼠标，恢复跟随模式
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());

        // 清空当前选择Actor，以及编辑模式状态
        SelectedActor   = nullptr;
        bEditRotateHeld = false;
        EditPanInput    = FVector2D::ZeroVector;

        // 清理绘制的路径
        bPathDragActive = false;
        DragPawn.Reset();

        
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        // 多路径统一清空
        LockedAIPaths.Reset();

        // 开始能量回复延时
        StartEnergyRegenWithDelay();

        UE_LOG(LogTemp, Log, TEXT("切换为跟随模式"));
    }

    UE_LOG(LogTemp, Log, TEXT("编辑模式判定参数值: %d"), bIsEditMode);

    UpdateInputContext();
}

void AInvisiblePlayerController::UpdateInputContext()
{
    if(ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {

            if(!Subsystem)
            {
                UE_LOG(LogTemp, Log, TEXT("增强输入子系统为空"));
                return;
            }

            // 清除原有增强输入
            Subsystem->ClearAllMappings();

            if(SwitchModeMappingContext)
            {
                Subsystem->AddMappingContext(SwitchModeMappingContext, 0);
                UE_LOG(LogTemp, Log, TEXT("切换功能增强输入激活"));
            }

            if(bIsEditMode)
            {
                if(EditModeMappingContext)
                {
                    // 添加编辑模式增强输入
                    Subsystem->AddMappingContext(EditModeMappingContext, 0);
                    UE_LOG(LogTemp, Log, TEXT("切换为编辑模式"));
                }
            }

            if(!bIsEditMode)
            {
                if(FollowMappingContext)
                {
                    // 添加跟随模式增强输入
                    Subsystem->AddMappingContext(FollowMappingContext, 0);
                    UE_LOG(LogTemp, Log, TEXT("切换为跟随模式"));
                }
            }
        }
    }
}


// =====跟随模式=====

// 移动输入
void AInvisiblePlayerController::OnMove(const FInputActionValue& Value)
{
    if (bGameplayInputLocked) return;
    if(bIsEditMode) return;

    // 获取玩家输入向量
    const FVector2D Axis = Value.Get<FVector2D>();
    if(Axis.IsNearlyZero()) return;

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());  // 获取玩家角色
    if(!PlayerCharacter) return;

    // 计算移动方向,以相机面向方向为参考
    const float CamYaw = PlayerCharacter->GetCameraYaw();
    const FRotator YawRot(0.0f, CamYaw, 0.0f);
    const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);  //相机前方向
    const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);    //相机右方向

    // 计算移动方向
    const FVector MoveDir = (Forward * Axis.Y + Right * Axis.X).GetSafeNormal();

    // 旋转角色置移动方向
    const float TargetYaw = FMath::RadiansToDegrees(FMath::Atan2(MoveDir.Y, MoveDir.X));
    const FRotator CurrentRot = PlayerCharacter->GetActorRotation();    // 获取玩家朝向
    const FRotator TargetRot(0.0f, TargetYaw, 0.0f);
    const FRotator NextRot = FMath::RInterpTo(CurrentRot, TargetRot, GetWorld()->GetDeltaSeconds(), CharacterRotateSpeed);
    PlayerCharacter->SetActorRotation(NextRot);


    // 移动角色
    PlayerCharacter->AddMovementInput(MoveDir, 1.0f);
}

// 相机旋转功能
// 旋转状态触发
void AInvisiblePlayerController::OnRotateHoldStarted()
{
    if (bGameplayInputLocked) return;

    bRotateHeld = true;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转启动"));
}

// 旋转状态结束
void AInvisiblePlayerController::OnRotateHoldCompleted()
{
    if (bGameplayInputLocked) return;

    bRotateHeld = false;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转结束"));
}

// 相机旋转
void AInvisiblePlayerController::OnRotate(const FInputActionValue& Value)
{
    if (bGameplayInputLocked) return;
    if(bIsEditMode) return;
    //if(!bRotateHeld) return;

    const float DeltaYaw = Value.Get<FVector2D>().X * OrbitYawSpeed;

    if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
    {
        PlayerCharacter->OrbitCamera(DeltaYaw);
    }
}


// 蹲下起立状态切换
void AInvisiblePlayerController::OnCrouchToggle()
{
    if (bGameplayInputLocked) return;
    if(bIsEditMode) return;

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

    if(!PlayerCharacter) return;

    bIsCrouching = !bIsCrouching;

    if(bIsCrouching)
    {
        if(bIsRunning)
        {
            OnRunCompleted();
        }

        PlayerCharacter->Crouch();
        UE_LOG(LogTemp, Log, TEXT("角色蹲下"));
    }
    else
    {
        PlayerCharacter->UnCrouch();
        UE_LOG(LogTemp, Log, TEXT("角色起立"));
    }
}


// 奔跑开始
void AInvisiblePlayerController::OnRunStarted()
{
    if (bGameplayInputLocked) return;
    if(bIsEditMode) return;
    if(bIsCrouching) return;
    
    bIsRunning = true;

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
    if(!PlayerCharacter) return;
    
    // 将最大速度设置为奔跑速度
    PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->RunSpeed;

    PlayerCharacter->bIsRunning = true;

    UE_LOG(LogTemp, Log, TEXT("奔跑开始"));
}


// 奔跑状态结束
void AInvisiblePlayerController::OnRunCompleted()
{
    if (bGameplayInputLocked) return;
    if(bIsEditMode) return;

    bIsRunning = false;
    
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
    if(!PlayerCharacter) return;

    PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->NormalWalkSpeed;
    PlayerCharacter->bIsRunning = false;

    UE_LOG(LogTemp, Log, TEXT("奔跑结束"));
    
}

// =====编辑模式=====
// 移动输入
void AInvisiblePlayerController::OnEditPan(const FInputActionValue& Value)
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode) return;
    EditPanInput = Value.Get<FVector2D>();
}

// 按键松开时清零输入
void AInvisiblePlayerController::OnEditPanCompleted()
{
    if (bGameplayInputLocked) return;

    EditPanInput = FVector2D::ZeroVector;
}

// 旋转状态触发
void AInvisiblePlayerController::OnEditRotateHoldStarted()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode) return;
    bEditRotateHeld = true;
    
    // 按住旋转键时隐藏光标
    //bShowMouseCursor = false;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转启动"));
}

// 每帧检测旋转按键是否被按住（配合 Tick 末尾重置）
// void AInvisiblePlayerController::OnEditRotateHold()
// {
//     if(!bIsEditMode) return;
//     bEditRotateHeld = true;   // Tick 末尾会重置

//     UE_LOG(LogTemp, Log, TEXT("镜头旋转启动"));
// }

// 旋转状态结束
void AInvisiblePlayerController::OnEditRotateHoldCompleted()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode) return;
    bEditRotateHeld = false;

    //bShowMouseCursor = true;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转结束"));
}

// 旋转输入
void AInvisiblePlayerController::OnEditRotate(const FInputActionValue& Value)
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode || !EditCamera) return;
    const float DeltaYaw = Value.Get<FVector2D>().X * EditCamera->CameraOrbitSpeed;
    EditCamera->OrbitCamera(DeltaYaw);
}

// 单位选择
void AInvisiblePlayerController::OnEditSelect()
{
    if(!bIsEditMode) return;

    // 旋转模式下屏蔽选择功能
    if(bEditRotateHeld) return;

    if (bGameplayInputLocked) return;

    FHitResult HitResult;
    if(GetHitResultUnderCursor(ECC_Pawn, false, HitResult))
    {
        AActor* HitActor = HitResult.GetActor();

        if(!HitActor) return;

        // 如果选中其他单位，则取消当前选中目标
        if(SelectedActor && SelectedActor != HitActor)
        {
            // 预留
        }
        SelectedActor = HitActor;
        UE_LOG(LogTemp, Log, TEXT("编辑模式选中: %s"), *HitActor->GetName());
    }
    else
    {
        // 点选非单位Actor，则取消选中
        if(SelectedActor)
        {
            // 预留
        }
        SelectedActor = nullptr;
        UE_LOG(LogTemp, Log, TEXT("编辑模式取消选中"));
    }
}


// ===== 编辑模式下“心控”功能输入 =====

// 开始路径绘制
void AInvisiblePlayerController::OnStartPathDrag()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode || bEditRotateHeld) return;
    
    // 重置状态
    ClearPreviewInteraction();
    bPathDragActive = false;
    DragPawn.Reset();

    bHasPreviewPath = false;
    PreviewTarget = FVector::ZeroVector;
    PreviewPathPoints.Reset();
    PreviewPathLength = 0.0f;
    PreviewEnergyCost = 0.0f;
    DragPawnOldPathCost = 0.0f;

    // 记录鼠标起始位置
    bPathActuallyDragged = false;
    PathDragStartMousePos = FVector2D::ZeroVector;
    float MouseX = 0.f, MouseY = 0.f;
    if (GetMousePosition(MouseX, MouseY))
    {
        PathDragStartMousePos = FVector2D(MouseX, MouseY);
    }

    // 优先检测 Pawn ，防止选中到其他Actor
    FHitResult PawnHit;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    const bool bHitPawn = GetHitResultUnderCursorForObjects(ObjectTypes, false, PawnHit);
    if (bHitPawn)
    {
        if (APawn* HitPawn = Cast<APawn>(PawnHit.GetActor()))
        {
            SelectedActor = HitPawn;
            // 只有敌方 AI 可拖拽
            if (Cast<AEnemyBase>(HitPawn))
            {
                
                DragPawn = HitPawn;
                bPathDragActive = true;
                UE_LOG(LogTemp, Log, TEXT("开始路径绘制: %s"), *HitPawn->GetName());

                // 记录旧路径消耗
                const int32 OldIndex = FindLockedPathIndexByPawn(HitPawn);
                if (OldIndex != INDEX_NONE)
                {
                    DragPawnOldPathCost = FMath::Max(0.0f, LockedAIPaths[OldIndex].EnergyCost);
                }

                DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
                
                // 显示敌方信息面板
                ShowAIInfoPanel(Cast<AEnemyBase>(HitPawn));
                return;
            }
            else
            {
                // 其他 Pawn（例如玩家）只选中，不拖拽
                
                DisplayPathEnergy = CurrentPathEnergy;
                UE_LOG(LogTemp, Log, TEXT("选中非AI Pawn: %s"), *HitPawn->GetName());

                // 隐藏敌方信息面板
                HideAIInfoPanel();
                return;
            }
        }
    }

    // 如果未选中 Pawn ，再检测物品
    FHitResult Hit;
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit) && Hit.GetActor())
    {
        SelectedActor = Hit.GetActor(); // 只选中，不拖拽

        if(SelectedActor)
        {
            UE_LOG(LogTemp, Log, TEXT("选中Actor: %s"), *SelectedActor->GetName());
        }
        

        // 隐藏敌方信息面板
        HideAIInfoPanel();
    }
    else
    {
        // 点空白则取消选中
        SelectedActor = nullptr;
        UE_LOG(LogTemp, Log, TEXT("编辑模式取消选中"));

        // 隐藏敌方信息面板
        HideAIInfoPanel();
    }

    UE_LOG(LogTemp, Log, TEXT("开始路径绘制"));
    if (SelectedActor)
    {
        UE_LOG(LogTemp, Log, TEXT("选中Actor: %s"), *SelectedActor->GetName());
    }
    
}

// 拖拽时更新路径预览
void AInvisiblePlayerController::OnEditPathDragTriggered()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode || !bPathDragActive || !DragPawn.IsValid()) return;

    // 如果鼠标位移没有超过阈值，则不认为是拖拽
    if (!bPathActuallyDragged)
    {
        float MouseX = 0.f, MouseY = 0.f;
        if (GetMousePosition(MouseX, MouseY))
        {
            const float PixelMoved = FVector2D::Distance(
                PathDragStartMousePos,
                FVector2D(MouseX, MouseY)
            );
            bPathActuallyDragged = (PixelMoved >= PathDragPixelThreshold);
        }
    }

    // 如果还没达到拖拽阈值：只保持显示，不生成预览、不扣预览能量
    if (!bPathActuallyDragged)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
        ClearPreviewInteraction();
        return;
    }

    FHitResult GroundHit;
    if(!GetHitResultUnderCursor(ECC_Visibility, false, GroundHit))
    {
        bHasPreviewPath = false;    // 清除预览路径
        PreviewTarget = FVector::ZeroVector;    // 清除预览目标
        PreviewPathPoints.Reset();    // 清除预览路径点
        PreviewPathLength = 0.0f;    // 清除预览路径长度
        PreviewEnergyCost = 0.0f;    // 清除预览能量消耗
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);    // 刷新当前能量
        ClearPreviewInteraction();
        return;
    }

    const FVector Start = DragPawn->GetActorLocation();
    const FVector Target = GroundHit.Location;

    UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, Start, Target, DragPawn.Get());
    if(!NavPath || !NavPath->IsValid() || NavPath->PathPoints.Num() < 2 || NavPath->IsPartial())
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.0f;
        PreviewEnergyCost = 0.0f;
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
        ClearPreviewInteraction();
        return;
    }
    

    const float CostPerUnit = FMath::Max(PathEnergyCostPerUnit, KINDA_SMALL_NUMBER);

    // 当前拖拽AI若已有路径，预览时应先“忽略它的旧消耗”
    const float AvailableEnergy = FMath::Max(0.0f, CurrentPathEnergy + DragPawnOldPathCost);
    const float MaxAllowedLength = AvailableEnergy / CostPerUnit;

    TArray<FVector> ClampedPoints;
    FVector ClampedTarget = FVector::ZeroVector;
    float UsedLength = 0.0f;

    if (!BuildClampedPathByEnergy(NavPath->PathPoints, MaxAllowedLength, ClampedPoints, ClampedTarget, UsedLength))
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
        ClearPreviewInteraction();
        return;
    }

    // 过近不生效
    if (UsedLength < MinPathDistance)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
        ClearPreviewInteraction();
        return;
    }

    bHasPreviewPath = true;
    PreviewPathPoints = MoveTemp(ClampedPoints);
    PreviewTarget = ClampedTarget;
    PreviewPathLength = UsedLength;
    PreviewEnergyCost = UsedLength * CostPerUnit;
    // 实时显示（不真实扣）
    DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost - PreviewEnergyCost, 0.f, MaxPathEnergy);
    ResolvePreviewInteractionUnderCursor();
    SnapPreviewPathEndToInteractionTargetXY();

    // 吸附后再按预算截断，防止吸附导致能量消耗超出，在预览时修正偏差
    const float CostPerUnitAfterSnap = FMath::Max(PathEnergyCostPerUnit, KINDA_SMALL_NUMBER);
    const float AvailableEnergyAfterSnap = FMath::Max(0.0f, CurrentPathEnergy + DragPawnOldPathCost);
    const float MaxAllowedLengthAfterSnap = AvailableEnergyAfterSnap / CostPerUnitAfterSnap;
    ReClampPreviewPathByCurrentBudget(MaxAllowedLengthAfterSnap);

    // 吸附/截断后再次校验最小长度
    if (PreviewPathLength < MinPathDistance || PreviewPathPoints.Num() < 2)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);
        ClearPreviewInteraction();
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("路径预览更新"));
}

// 拖拽结束，保留路径直到编辑模式关闭
void AInvisiblePlayerController::OnEditPathDragCompleted()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode) return;

    bPathDragActive = false;

    // 防误触提交
    if (!bPathActuallyDragged)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DragPawnOldPathCost = 0.f;
        DisplayPathEnergy = CurrentPathEnergy;
        ClearPreviewInteraction();
        return;
    }

    if(!DragPawn.IsValid() || !bHasPreviewPath || PreviewPathPoints.Num() < 2)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DragPawnOldPathCost = 0.f;
        DisplayPathEnergy = CurrentPathEnergy;
        ClearPreviewInteraction();
        return;
    }

    const APawn* DraggingPawn = DragPawn.Get();
    const int32 Index = FindLockedPathIndexByPawn(DraggingPawn);
    const float OldCommittedCost = (Index != INDEX_NONE) ? FMath::Max(0.f, LockedAIPaths[Index].EnergyCost) : 0.f;  // 保留旧路径消耗

    const bool bInteractionValid = bHasPreviewInteraction && PreviewInteractionTargetActor.IsValid() && PreviewCandidateActions.Num() > 0;
    
    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[绘制完成] 绘制交互路径 bHasPreviewInteraction=%d TargetValid=%d CandidateNum=%d => bInteractionValid=%d"),
    // bHasPreviewInteraction ? 1 : 0,
    // PreviewInteractionTargetActor.IsValid() ? 1 : 0,
    // PreviewCandidateActions.Num(),
    // bInteractionValid ? 1 : 0);
    SnapPreviewPathEndToInteractionTargetXY();

    // 最后再按预算截断，防止提交时能量消耗超出，提交前兜底
    const float CostPerUnitFinal = FMath::Max(PathEnergyCostPerUnit, KINDA_SMALL_NUMBER);
    const float AvailableEnergyFinal = FMath::Max(0.0f, CurrentPathEnergy + OldCommittedCost);
    const float MaxAllowedLengthFinal = AvailableEnergyFinal / CostPerUnitFinal;

    if (!ReClampPreviewPathByCurrentBudget(MaxAllowedLengthFinal) || PreviewPathPoints.Num() < 2 || PreviewPathLength < MinPathDistance)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DragPawnOldPathCost = 0.f;
        DisplayPathEnergy = CurrentPathEnergy;
        ClearPreviewInteraction();
        return;
    }

    if(Index == INDEX_NONE)
    {
        FLockedAIPath NewPath;
        NewPath.OwnerPawn = DragPawn;
        NewPath.Target = PreviewTarget;
        NewPath.Points = PreviewPathPoints;
        NewPath.PathLength = PreviewPathLength;
        NewPath.EnergyCost = PreviewEnergyCost;

        // 互动上下文
        NewPath.TargetActor = PreviewInteractionTargetActor;
        NewPath.bIsInteractionPath = bInteractionValid;
        NewPath.CandidateActions = PreviewCandidateActions;

        // 提交时默认未确认动作
        NewPath.bActionConfirmed = false;
        NewPath.ConfirmedActionTag = FGameplayTag();
        NewPath.ConfirmedActionCost = 0.0f;
        NewPath.ConfirmedExecutionRadius = 0.0f;
        NewPath.ConfirmedDuration = 0.0f;
        LockedAIPaths.Add(MoveTemp(NewPath));

        AEnemyBase* SourceEnemy = Cast<AEnemyBase>(DragPawn.Get());
        AActor* TargetActor = PreviewInteractionTargetActor.Get();

        // 隐藏所有头顶交互按钮
        HideAllInteractionButtons();
        // 显示目标头顶交互按钮
        if (bInteractionValid && SourceEnemy && TargetActor)
        {
            const TArray<FInteractionActionOption>& Actions = (Index == INDEX_NONE) ? LockedAIPaths.Last().CandidateActions : LockedAIPaths[Index].CandidateActions;
            
            // UE_LOG(LogAIInteractionDebug, Log, TEXT("[绘制完成] 尝试显示按钮 Source=%s Target=%s ActionsNum=%d"),
            // *GetNameSafe(SourceEnemy), *GetNameSafe(TargetActor), Actions.Num());

            // TargetEnemy->ShowInteractionButtons(Actions, SourceEnemy);
            
            if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
            {
                TargetEnemy->ShowInteractionButtons(Actions, SourceEnemy);
            }
            else if (UInteractionTargetComponent* TargetComp = TargetActor ? TargetActor->FindComponentByClass<UInteractionTargetComponent>() : nullptr)
            {
                if (!TargetComp->OnInteractionActionChosen.IsAlreadyBound(this, &AInvisiblePlayerController::OnInteractionActionChosen))
                {
                    TargetComp->OnInteractionActionChosen.AddDynamic(this, &AInvisiblePlayerController::OnInteractionActionChosen);
                }
                TargetComp->ShowInteractionButtons(Actions, SourceEnemy);
            }
        }
    }
    else
    {
        LockedAIPaths[Index].Target = PreviewTarget;
        LockedAIPaths[Index].Points = PreviewPathPoints;
        LockedAIPaths[Index].PathLength = PreviewPathLength;
        LockedAIPaths[Index].EnergyCost = PreviewEnergyCost;

        // 互动上下文
        LockedAIPaths[Index].TargetActor = PreviewInteractionTargetActor;
        LockedAIPaths[Index].bIsInteractionPath = bInteractionValid;
        LockedAIPaths[Index].CandidateActions = PreviewCandidateActions;

        // 路径替换时，旧确认状态清空，避免残留
        LockedAIPaths[Index].bActionConfirmed = false;
        LockedAIPaths[Index].ConfirmedActionTag = FGameplayTag();
        LockedAIPaths[Index].ConfirmedActionCost = 0.0f;
        LockedAIPaths[Index].ConfirmedExecutionRadius = 0.0f;
        LockedAIPaths[Index].ConfirmedDuration = 0.0f;

        // 隐藏所有ai头顶交互按钮
        HideAllInteractionButtons();

        // 显示目标ai头顶交互按钮
        AEnemyBase* SourceEnemy = Cast<AEnemyBase>(DragPawn.Get());
        AActor* TargetActor = PreviewInteractionTargetActor.Get();

        // AI-物体现在暂时不会显示按钮，后续添加相关逻辑

        if (bInteractionValid && SourceEnemy && TargetActor)
        {
            const TArray<FInteractionActionOption>& Actions = LockedAIPaths[Index].CandidateActions;
            // TargetEnemy->ShowInteractionButtons(Actions, SourceEnemy);

            if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
            {
                TargetEnemy->ShowInteractionButtons(Actions, SourceEnemy);
            }
            else if (UInteractionTargetComponent* TargetComp = TargetActor->FindComponentByClass<UInteractionTargetComponent>())
            {
                if (!TargetComp->OnInteractionActionChosen.IsAlreadyBound(this, &AInvisiblePlayerController::OnInteractionActionChosen))
                {
                    TargetComp->OnInteractionActionChosen.AddDynamic(this, &AInvisiblePlayerController::OnInteractionActionChosen);
                }
                TargetComp->ShowInteractionButtons(Actions, SourceEnemy);
            }
        }
    }

    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy + OldCommittedCost - PreviewEnergyCost, 0.f, MaxPathEnergy);

    bHasPreviewPath = false;
    PreviewTarget = FVector::ZeroVector;
    PreviewPathPoints.Reset();
    PreviewPathLength = 0.0f;
    PreviewEnergyCost = 0.0f;
    DragPawnOldPathCost = 0.0f;
    DisplayPathEnergy = CurrentPathEnergy;
    ClearPreviewInteraction();

    UE_LOG(LogTemp, Log, TEXT("路径拖拽结束"));
}

// 绘制路径
void AInvisiblePlayerController::DrawPathPoints(const TArray<FVector>& Points, const FColor& Color) const
{
    if(Points.Num() < 2) return;

    for(int32 i=0; i<Points.Num()-1; ++i)
    {
        FVector A = Points[i] + FVector(0,0,PathDebugZOffset);
        FVector B = Points[i+1] + FVector(0,0,PathDebugZOffset);
        DrawDebugLine(GetWorld(), A, B, Color, false, 0.f, 0, 3.f);
    }
}

// 将预览路径终点XY吸附到预览目标中心（保留原终点Z）成功返回true
bool AInvisiblePlayerController::SnapPreviewPathEndToInteractionTargetXY()
{
    if (!bHasPreviewPath || PreviewPathPoints.Num() < 2)
    {
        return false;
    }

    if (!bHasPreviewInteraction || !PreviewInteractionTargetActor.IsValid())
    {
        return false;
    }

    AActor* TargetActor = PreviewInteractionTargetActor.Get();
    if (!TargetActor)
    {
        return false;
    }

    FVector Center = TargetActor->GetActorLocation();
    FVector BoundsOrigin = FVector::ZeroVector;
    FVector BoundsExtent = FVector::ZeroVector;
    TargetActor->GetActorBounds(true, BoundsOrigin, BoundsExtent);
    Center = BoundsOrigin; // 目标在世界坐标下的中心

    FVector& EndPoint = PreviewPathPoints.Last();
    const float PreservedZ = EndPoint.Z;

    // 仅锁定XY中心
    EndPoint.X = Center.X;
    EndPoint.Y = Center.Y;
    EndPoint.Z = PreservedZ; // 保持原路径终点高度

    // 若XY中心不可走，投影到附近
    // 获取当前世界的导航系统实例
    if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
    {
        // 声明一个存储投影后导航点的变量
        FNavLocation Projected;

        // 把 EndPoint 投影到导航网格上
        // 参数：原始目标点 | 输出投影后的点 | 投影搜索范围(XY120/Z300)
        if (NavSys->ProjectPointToNavigation(EndPoint, Projected, FVector(120.f, 120.f, 300.f)))
        {
            // 投影成功：更新目标点的 X、Y 为导航网格上的合法坐标
            EndPoint.X = Projected.Location.X;
            EndPoint.Y = Projected.Location.Y;
            // Z 轴高度保持原来的预设值
            EndPoint.Z = PreservedZ;
        }
    }

    PreviewTarget = EndPoint;
    
    // 终点变化后重算长度与能量显示
    PreviewPathLength = CalcPathLength(PreviewPathPoints);
    PreviewEnergyCost = PreviewPathLength * FMath::Max(PathEnergyCostPerUnit, KINDA_SMALL_NUMBER);
    DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost - PreviewEnergyCost, 0.f, MaxPathEnergy);

    return true;
}

// 吸附后按能量重新截断预览路径
bool AInvisiblePlayerController::ReClampPreviewPathByCurrentBudget(float MaxAllowedLength)
{
    if (!bHasPreviewPath || PreviewPathPoints.Num() < 2)
    {
        return false;
    }

    TArray<FVector> ClampedPoints;
    FVector ClampedTarget = FVector::ZeroVector;
    float UsedLength = 0.0f;

    if (!BuildClampedPathByEnergy(PreviewPathPoints, MaxAllowedLength, ClampedPoints, ClampedTarget, UsedLength))
    {
        return false;
    }

    PreviewPathPoints = MoveTemp(ClampedPoints);
    PreviewTarget = ClampedTarget;
    PreviewPathLength = UsedLength;
    PreviewEnergyCost = UsedLength * FMath::Max(PathEnergyCostPerUnit, KINDA_SMALL_NUMBER);
    DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost - PreviewEnergyCost, 0.f, MaxPathEnergy);
    
    return true;
}


// 删除当前选中的ai路径
void AInvisiblePlayerController::OnRemoveSelectedAIPath()
{
    if (bGameplayInputLocked) return;
    if(!bIsEditMode) return;

    // 选中时才能删除
    const APawn* SelectedPawn = Cast<APawn>(SelectedActor);
    if(!SelectedPawn || !Cast<AEnemyBase>(SelectedPawn))
    {
        UE_LOG(LogTemp, Log, TEXT("未选中AI Pawn,不删除路径"));
        return;
    }

    // 计算可退还的能量
    float Refund = 0.f;
    for (const FLockedAIPath& Item : LockedAIPaths)
    {
        if (Item.OwnerPawn.Get() == SelectedPawn)
        {
            Refund += FMath::Max(0.f, Item.EnergyCost);

            // 已确认动作时，额外返还互动能量
            if (Item.bActionConfirmed)
            {
                Refund += FMath::Max(0.f, Item.ConfirmedActionCost);
            }
        }
    }

    const int32 RemovedCount = LockedAIPaths.RemoveAll(
        [SelectedPawn](const FLockedAIPath& Item)
        {
            return Item.OwnerPawn.Get() == SelectedPawn;
        });

    if(RemovedCount <= 0)
    {
        UE_LOG(LogTemp, Log, TEXT("该AI没有可删除路径: %s"), *SelectedPawn->GetName());
        return;
    }

    // 删除后隐藏所有ai头顶交互按钮
    if(RemovedCount > 0)
    {
        HideAllInteractionButtons();
    }

    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy + Refund, 0.f, MaxPathEnergy);
    DisplayPathEnergy = CurrentPathEnergy;

    // 如果当前正在拖拽的就是这个AI，清理预览
    if(DragPawn.Get() == SelectedPawn)
    {
        bPathDragActive = false;
        DragPawn.Reset();
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.0f;
        PreviewEnergyCost = 0.0f;
        DragPawnOldPathCost = 0.0f;
        ClearPreviewInteraction();
    }

    //RefreshCurrentPathEnergy();
    if(SelectedPawn)
    {
        UE_LOG(LogTemp, Log, TEXT("已删除AI路径: %s, 删除数量: %d"), *SelectedPawn->GetName(), RemovedCount);
    }
    
}

// 计算路径长度
float AInvisiblePlayerController::CalcPathLength(const TArray<FVector>& Points) const
{
    if (Points.Num() < 2) return 0.0f;

    float Sum = 0.0f;
    for (int32 i = 1; i < Points.Num(); ++i)
    {
        Sum += FVector::Dist(Points[i - 1], Points[i]);
    }
    return Sum;
}

// 按可用能量截断路径
bool AInvisiblePlayerController::BuildClampedPathByEnergy(
    const TArray<FVector>& InPoints,
    float MaxAllowedLength,
    TArray<FVector>& OutPoints,
    FVector& OutTarget,
    float& OutUsedLength) const
{
    OutPoints.Reset();
    OutTarget = FVector::ZeroVector;
    OutUsedLength = 0.0f;

    if (InPoints.Num() < 2 || MaxAllowedLength <= KINDA_SMALL_NUMBER)
    {
        return false;
    }

    OutPoints.Add(InPoints[0]);
    float Remaining = MaxAllowedLength;    // 剩余可用能量

    for (int32 i = 1; i < InPoints.Num(); ++i)
    {
        const FVector A = InPoints[i - 1];
        const FVector B = InPoints[i];
        const float SegLen = FVector::Dist(A, B);

        if (SegLen <= KINDA_SMALL_NUMBER) continue;    // 忽略极短距离

        if (SegLen <= Remaining + KINDA_SMALL_NUMBER)    // 如果当前段长度小于剩余能量，则截取当前段
        {
            OutPoints.Add(B);
            OutUsedLength += SegLen;
            Remaining -= SegLen;
        }
        else
        {
            const float Alpha = FMath::Clamp(Remaining / SegLen, 0.f, 1.f);
            const FVector CutPoint = FMath::Lerp(A, B, Alpha);
            OutPoints.Add(CutPoint);
            OutUsedLength += Remaining;
            Remaining = 0.f;
            break;
        }
    }

    if (OutPoints.Num() < 2)
    {
        OutPoints.Reset();
        return false;
    }

    OutTarget = OutPoints.Last();
    return true;
}

// 查找指定pawn的已锁定路径索引
int32 AInvisiblePlayerController::FindLockedPathIndexByPawn(const APawn* InPawn) const
{
    if (!InPawn) return INDEX_NONE;

    for (int32 i = 0; i < LockedAIPaths.Num(); ++i)
    {
        if (LockedAIPaths[i].OwnerPawn.Get() == InPawn)
        {
            return i;
        }
    }
    return INDEX_NONE;
}

// 计算指定pawn已使用的能量
float AInvisiblePlayerController::GetCommittedEnergyUsed(const APawn* IgnorePawn) const
{
    float Used = 0.0f;
    for (const FLockedAIPath& Item : LockedAIPaths)
    {
        if (!Item.OwnerPawn.IsValid()) continue;
        if (IgnorePawn && Item.OwnerPawn.Get() == IgnorePawn) continue;
        Used += Item.EnergyCost;
    }
    return Used;
}

// 刷新当前能量
void AInvisiblePlayerController::RefreshCurrentPathEnergy()
{
    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy, 0.f, MaxPathEnergy);
    if(!bPathDragActive)
    {
        DisplayPathEnergy = CurrentPathEnergy;
    }
}


// =====能量回复功能=====
// 开始能量回复延时
void AInvisiblePlayerController::StartEnergyRegenWithDelay()
{
    StopEnergyRegen();

    // 如果当前能量已满，则不回复
    if(CurrentPathEnergy >= MaxPathEnergy) return;

    GetWorldTimerManager().SetTimer(
        EnergyRegenTimerHandle,
        this,
        &AInvisiblePlayerController::BeginEnergyRegen,
        FMath::Max(0.0f, EnergyRegenDelay),
        false
    );

    UE_LOG(LogTemp, Log, TEXT("能量回复延时启动，延迟: %f秒"), EnergyRegenDelay);
}

// 开始能量回复
void AInvisiblePlayerController::BeginEnergyRegen()
{
    if(bIsEditMode) return;
    bIsRegenEnergy = true;
}

// 停止能量回复
void AInvisiblePlayerController::StopEnergyRegen()
{
    // 清理计时器，防止多次触发
    GetWorldTimerManager().ClearTimer(EnergyRegenTimerHandle);
    bIsRegenEnergy = false;
}

// 每帧更新能量回复
void AInvisiblePlayerController::TickEnergyRegen(float DeltaTime)
{
    if(!bIsRegenEnergy) return;
    if(bIsEditMode) return;

    CurrentPathEnergy = FMath::Min(MaxPathEnergy, CurrentPathEnergy + DeltaTime * EnergyRegenRate);
    DisplayPathEnergy = CurrentPathEnergy;

    if(CurrentPathEnergy >= MaxPathEnergy - KINDA_SMALL_NUMBER)
    {
        CurrentPathEnergy = MaxPathEnergy;
        DisplayPathEnergy = CurrentPathEnergy;
        bIsRegenEnergy = false;
    }
}


// ===== ai单位信息显示功能 =====
// 显示ai单位信息面板
void AInvisiblePlayerController::ShowAIInfoPanel(AEnemyBase* InEnemy)
{
    if(!AIInfoPanelInstance || !InEnemy) return;

    const FAIInfoData PanelData = InEnemy->BuildAIInfoDataForPanel(this, true);
    AIInfoPanelInstance->UpdateAIInfo(PanelData, InEnemy);
    AIInfoPanelInstance->SetVisibility(ESlateVisibility::Visible);

    UE_LOG(LogTemp, Log, TEXT("显示敌方信息面板"));
}

// 隐藏ai单位信息面板
void AInvisiblePlayerController::HideAIInfoPanel()
{
    if(!AIInfoPanelInstance) return;
    AIInfoPanelInstance->SetVisibility(ESlateVisibility::Hidden);
}


// ===== ai交互功能 =====
// 清除预览交互
void AInvisiblePlayerController::ClearPreviewInteraction()
{
    bHasPreviewInteraction = false;
    PreviewInteractionTargetActor.Reset();
    PreviewCandidateActions.Reset();
}

// 解析预览交互
void AInvisiblePlayerController::ResolvePreviewInteractionUnderCursor()
{
    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[解析预览交互] DragPawn=%s bHasPreviewPath=%d"),*GetNameSafe(DragPawn.Get()), bHasPreviewPath ? 1 : 0);

    ClearPreviewInteraction();
    
    if(!DragPawn.IsValid() || !bHasPreviewPath)
    {
        UE_LOG(LogAIInteractionDebug, Warning, TEXT("[解析预览交互] 条件不满足，返回"));
        return;
    }

    AEnemyBase* SourceEnemy = Cast<AEnemyBase>(DragPawn.Get());
    if(!SourceEnemy)
    {
        return;
    }

    FHitResult Hit;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));   // AI-AI互动用
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));   // AI-物体互动用

    const bool bHit = GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);

    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[解析预览交互] bHit=%d HitActor=%s"),
    // bHit ? 1 : 0, *GetNameSafe(Hit.GetActor()));

    if(!bHit)
    {
        // UE_LOG(LogAIInteractionDebug, Warning, TEXT("[解析预览交互] return，鼠标下没有Pawn"));
        return;
    }

    AActor* HitActor = Hit.GetActor();
    // AEnemyBase* TargetEnemy = Cast<AEnemyBase>(HitActor);

    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[解析预览交互] Source=%s Target=%s IsSelf=%d"),
    // *GetNameSafe(SourceEnemy), *GetNameSafe(TargetEnemy), (TargetEnemy == SourceEnemy) ? 1 : 0);

    if(!HitActor || HitActor == SourceEnemy)
    {
        // UE_LOG(LogAIInteractionDebug, Warning, TEXT("[解析预览交互] return: 不存在Target或Target与Source相同"));
        return;
    }

    const bool bIsEnemyTarget = Cast<AEnemyBase>(HitActor) != nullptr;
    const bool bHasInteractionComp = HitActor->FindComponentByClass<UInteractionTargetComponent>() != nullptr;
    if (!bIsEnemyTarget && !bHasInteractionComp)
    {
        return; // 场景普通物体，非可互动目标
    }

    TArray<FInteractionActionOption> Candidates;
    const bool bBuilt = BuildInteractionCandidates(SourceEnemy, HitActor, Candidates);
    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[解析预览交互] 建立预览 bBuilt=%d Num=%d"),
    // bBuilt ? 1 : 0, Candidates.Num());

    if(bBuilt)
    {
        bHasPreviewInteraction = true;
        PreviewInteractionTargetActor = HitActor;
        PreviewCandidateActions = MoveTemp(Candidates);

        // UE_LOG(LogAIInteractionDebug, Log, TEXT("[解析预览交互] 设置预览交互 Target=%s Num=%d"),
        // *GetNameSafe(PreviewInteractionTargetActor.Get()), PreviewCandidateActions.Num());
    }
}


// 构建交互候选者
bool AInvisiblePlayerController::BuildInteractionCandidates(AEnemyBase* SourceAI, AActor* TargetActor, TArray<FInteractionActionOption>& OutActions) const
{
    OutActions.Reset();

    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] 进入 Source=%s Target=%s TraitActionProfile=%s"),
    // *GetNameSafe(SourceAI), *GetNameSafe(TargetActor), *GetNameSafe(TraitActionProfile));

    if(!SourceAI || !TargetActor || SourceAI == TargetActor)
    {
        return false;
    }

    const UWorld* World = GetWorld();
    if(!World) return false;

    // 如果已有锁定行为，则只执行锁定行为
    if (const FInteractionPairDecisionLock* PairLock = FindPairDecisionLock(SourceAI, TargetActor))
    {
        if (PairLock->bActive && PairLock->LockedOption.Spec.IsValid())
        {
            OutActions.Reset();
            OutActions.Add(PairLock->LockedOption); // 只显示锁定行为
            return true;
        }
    }

    // 获取特质子系统
    UGameInstance* GI = World->GetGameInstance();
    UTraitSubsystem* TraitSub = GI ? GI->GetSubsystem<UTraitSubsystem>() : nullptr;
    if(!TraitSub) 
    {
        UE_LOG(LogAIInteractionDebug, Error, TEXT("[构建预览交互] return: 特质子系统为空"));
        return false;
    }

    // 获取目标标签容器
    FGameplayTagContainer TargetTags;
    if(TargetActor->GetClass()->ImplementsInterface(UTraitTargetInterface::StaticClass()))
    {
        TargetTags = ITraitTargetInterface::Execute_GetInteractionTargetTags(TargetActor);
        UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] 获取目标标签 TargetTags=%s"), *TargetTags.ToString());
    }
    else if (const UInteractionTargetComponent* TargetComp = TargetActor->FindComponentByClass<UInteractionTargetComponent>())
    {
        TargetTags = TargetComp->GetInteractionTargetTags();
    }

    // 根据目标类型决定交互类型
    const ETraitInteractionType WantedType = 
        Cast<AEnemyBase>(TargetActor)
        ? ETraitInteractionType::AI_With_AI
        : ETraitInteractionType::AI_With_Object;

    // 解析 SourceEnemy 的特质，并将ai与ai的特质写入输出数组
    TArray<UTraitDefinition*> TraitDefs;
    TraitSub->ResolveTraitDefs(SourceAI->TraitTags, TraitDefs);

    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] 解析 SourceEnemy 的特质，并将ai与ai的特质写入输出数组 TraitDefs=%d"), TraitDefs.Num());

    TSet<FGameplayTag> UniqueActionTags;

    for(const UTraitDefinition* Def : TraitDefs)
    {
        if(!Def) continue;

        for(const FTraitInteractionRule& Rule : Def->Rules)
        {
            // UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] Rule Type=%d Suggested=%s ActionTag=%s TargetFilter=%s"),
            // (int32)Rule.InteractionType,
            // *Rule.SuggestedBehaviorTag.ToString(),
            // *Rule.InteractionActionTag.ToString(),
            // *Rule.TargetTagsAny.ToStringSimple());

            if(Rule.InteractionType != WantedType)
            {
                // UE_LOG(LogAIInteractionDebug, Warning, TEXT("[构建预览交互] Skip: target filter failed"));
                continue;
            }

            const bool bPassTargetFilter = Rule.TargetTagsAny.IsEmpty() || TargetTags.HasAny(Rule.TargetTagsAny);
            if(!bPassTargetFilter)
            {
                continue;
            }

            const FTraitResolvedAction Resolved = UTraitActionResolver::ResolveAction(Rule, TraitActionProfile);

            // UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] Resolved Valid=%d Tag=%s Text=%s Cost=%.2f Radius=%.2f Duration=%.2f"),
            // Resolved.bValid ? 1 : 0,
            // *Resolved.ActionTag.ToString(),
            // *Resolved.ButtonText.ToString(),
            // Resolved.EnergyCost,
            // Resolved.ExecutionRadius,
            // Resolved.Duration);

            if(!Resolved.bValid || !Resolved.ActionTag.IsValid())
            {
                // UE_LOG(LogAIInteractionDebug, Warning, TEXT("[构建预览交互] Skip: invalid or empty action tag"));
                continue;
            }

            // 对Tag进行去重操作
            if(UniqueActionTags.Contains(Resolved.ActionTag))
            {
                continue;
            }
            UniqueActionTags.Add(Resolved.ActionTag);

            FInteractionActionOption NewOption;
            NewOption.ButtonText = Resolved.ButtonText;
            NewOption.Spec.ActionTag = Resolved.ActionTag;
            NewOption.Spec.EnergyCost = FMath::Max(0.0f, Resolved.EnergyCost);
            NewOption.Spec.ExecutionRadius = FMath::Max(0.0f, Resolved.ExecutionRadius);
            NewOption.Spec.Duration = FMath::Max(0.0f, Resolved.Duration);

            OutActions.Add(MoveTemp(NewOption));

            if(OutActions.Num() >= FMath::Clamp(MaxInteractionButtons, 1, 5))
            {
                return true;
            }
        }
    }
    // UE_LOG(LogAIInteractionDebug, Log, TEXT("[构建预览交互] 退出 OutActions=%d"), OutActions.Num());
    return OutActions.Num() > 0;
}

// 注册ai交互委托
void AInvisiblePlayerController::RegisterEnemyInteractionDelegates()
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);

    for(AActor* Enemy : FoundEnemies)
    {
        AEnemyBase* EnemyBase = Cast<AEnemyBase>(Enemy);
        if(!EnemyBase) continue;

        if(!EnemyBase->OnInteractionActionChosen.IsAlreadyBound(this, &AInvisiblePlayerController::OnInteractionActionChosen))
        {
            EnemyBase->OnInteractionActionChosen.AddDynamic(this, &AInvisiblePlayerController::OnInteractionActionChosen);
        }
    }

}

// 注销ai交互委托
void AInvisiblePlayerController::UnregisterEnemyInteractionDelegates()
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);
    
    for(AActor* Enemy : FoundEnemies)
    {
        AEnemyBase* EnemyBase = Cast<AEnemyBase>(Enemy);
        if(!EnemyBase) continue;

        EnemyBase->OnInteractionActionChosen.RemoveDynamic(this, &AInvisiblePlayerController::OnInteractionActionChosen);
    }
}

// 交互行为选择句柄
void AInvisiblePlayerController::OnInteractionActionChosen(
    FInteractionActionOption ActionData,
    AEnemyBase* SourceAI,
    AActor* TargetActor)
{
    if (!bIsEditMode || !SourceAI || !TargetActor)
    {
        return;
    }

    // 进行路径查找
    const int32 PathIndex = FindLockedInteractionPathIndex(SourceAI, TargetActor);
    // 未找到路径
    if (PathIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Warning, TEXT("未找到对应互动路径: Source=%s Target=%s"),
            *GetNameSafe(SourceAI), *GetNameSafe(TargetActor));
        return;
    }

    // 获取最终执行行为
    FInteractionActionOption FinalOption;
    bool bShouldCreatePairLock = false;
    if (!TryResolveLockedOrNewPairDecision(SourceAI, TargetActor, ActionData, FinalOption, bShouldCreatePairLock))
    {
        return;
    }

    // 获取路径并对比新路径与旧路径能量消耗
    FLockedAIPath& Path = LockedAIPaths[PathIndex];
    const float NewCost = FMath::Max(0.0f, FinalOption.Spec.EnergyCost);
    const float OldCost = Path.bActionConfirmed ? FMath::Max(0.0f, Path.ConfirmedActionCost) : 0.0f;
    const float DeltaCost = NewCost - OldCost; // >0 需要额外扣能，<0 返还差额

    if (DeltaCost > 0.0f && CurrentPathEnergy + KINDA_SMALL_NUMBER < DeltaCost)
    {
        UE_LOG(LogTemp, Warning, TEXT("互动能量不足: Need=%.2f Current=%.2f"), DeltaCost, CurrentPathEnergy);
        return;
    }

    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy - DeltaCost, 0.0f, MaxPathEnergy);
    DisplayPathEnergy = CurrentPathEnergy;

    Path.bActionConfirmed = true;
    Path.ConfirmedActionTag = FinalOption.Spec.ActionTag;
    Path.ConfirmedActionCost = NewCost;
    Path.ConfirmedExecutionRadius = FMath::Max(0.0f, FinalOption.Spec.ExecutionRadius);
    Path.ConfirmedDuration = FMath::Max(0.0f, FinalOption.Spec.Duration);

    // 只有确认成功后才创建 Pair 锁
    if (bShouldCreatePairLock)
    {
        SetPairDecisionLock(SourceAI, TargetActor, FinalOption);
    }

    // 点击后隐藏按钮
    HideAllInteractionButtons();

    // 打印日志
    UE_LOG(LogTemp, Log, TEXT("交互行为选择: Source=%s Target=%s Action=%s Cost=%.2f"),
        SourceAI ? *SourceAI->GetName() : TEXT("None"),
        TargetActor ? *TargetActor->GetName() : TEXT("None"),
        *FinalOption.Spec.ActionTag.ToString(),
        FinalOption.Spec.EnergyCost);
}



// 隐藏所有头顶交互按钮
void AInvisiblePlayerController::HideAllInteractionButtons()
{
    // 隐藏AI-AI互动按钮
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);
    
    for (AActor* EnemyActor : FoundEnemies)
    {
        if (AEnemyBase* Enemy = Cast<AEnemyBase>(EnemyActor))
        {
            Enemy->HideInteractionButtons();
        }
    }

    // 隐藏AI-物体互动按钮
    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
    
    for (AActor* Actor : AllActors)
    {
        if (!Actor) continue;
        if (UInteractionTargetComponent* TargetComp = Actor->FindComponentByClass<UInteractionTargetComponent>())
        {
            TargetComp->HideInteractionButtons();
        }
    }
}

// 查找从 SourceAI 到 TargetAI 的互动路径
int32 AInvisiblePlayerController::FindLockedInteractionPathIndex(const AEnemyBase* SourceAI, const AActor* TargetActor) const
{
    if(!SourceAI || !TargetActor) return INDEX_NONE;

    for(int32 i = 0; i < LockedAIPaths.Num(); ++i)
    {
        const FLockedAIPath& Item = LockedAIPaths[i];
        if(!Item.bIsInteractionPath) continue;

        const AActor* SourceActor = Item.OwnerPawn.Get();
        const AActor* Target = Item.TargetActor.Get();

        if(SourceActor == SourceAI && Target == TargetActor)
        {
            return i;
        }
    }

    return INDEX_NONE;
}


// ===== 斗殴替换聊天、并且锁定第一次行为的功能 =====

// 判断是否为聊天类行为
bool AInvisiblePlayerController::IsChatEntryAction(const FGameplayTag& ActionTag) const
{
    return ChatBehaviorRootTag.IsValid() && ActionTag.IsValid() && ActionTag.MatchesTag(ChatBehaviorRootTag);
}


// 查找双方互动锁（只读）
const FInteractionPairDecisionLock* AInvisiblePlayerController::FindPairDecisionLock(
    const AActor* SourceActor,
    const AActor* TargetActor) const
{
    if (!SourceActor || !TargetActor) return nullptr;
    return InteractionPairDecisionLocks.Find(FInteractionPairKey(SourceActor, TargetActor));
}

// 查找双方互动锁（可读写）
FInteractionPairDecisionLock* AInvisiblePlayerController::FindPairDecisionLockMutable(
    const AActor* SourceActor,
    const AActor* TargetActor)
{
    if (!SourceActor || !TargetActor) return nullptr;
    return InteractionPairDecisionLocks.Find(FInteractionPairKey(SourceActor, TargetActor));
}

// 设置双方互动锁
void AInvisiblePlayerController::SetPairDecisionLock(
    const AActor* SourceActor,
    const AActor* TargetActor,
    const FInteractionActionOption& LockedOption)
{
    if (!SourceActor || !TargetActor) return;

    FInteractionPairDecisionLock& Slot = InteractionPairDecisionLocks.FindOrAdd(FInteractionPairKey(SourceActor, TargetActor));
    Slot.bActive = true;
    Slot.LockedOption = LockedOption;
}


// 清除双方互动锁
void AInvisiblePlayerController::ClearPairDecisionLock(
    const AActor* SourceActor,
    const AActor* TargetActor)
{
    if (!SourceActor || !TargetActor) return;
    InteractionPairDecisionLocks.Remove(FInteractionPairKey(SourceActor, TargetActor));
}

// 尝试从 ActionProfile 读取行为的默认参数（能量/距离/时长）
bool AInvisiblePlayerController::TryBuildOptionFromActionProfile(
    const FGameplayTag& ActionTag,
    const FText& FallbackText,
    FInteractionActionOption& OutOption) const
{
    OutOption = FInteractionActionOption();

    if (!ActionTag.IsValid() || !TraitActionProfile)
    {
        return false;
    }

    FTraitActionProfileEntry Entry;
    if (!TraitActionProfile->FindActionProfile(ActionTag, Entry))
    {
        return false;
    }

    OutOption.ButtonText = Entry.DefaultButtonText.IsEmpty() ? FallbackText : Entry.DefaultButtonText;
    OutOption.Spec.ActionTag = ActionTag;
    OutOption.Spec.EnergyCost = FMath::Max(0.0f, Entry.DefaultEnergyCost);
    OutOption.Spec.ExecutionRadius = FMath::Max(0.0f, Entry.DefaultExecutionRadius);
    OutOption.Spec.Duration = FMath::Max(0.0f, Entry.DefaultDuration);

    return OutOption.Spec.IsValid();
}

// 从 TraitDefinition 的整套解析方案中获取配置值
bool AInvisiblePlayerController::TryResolveFinalOptionFromTraitRules(
    AEnemyBase* SourceAI,
    AActor* TargetActor,
    const FGameplayTag& WantedActionTag,
    const FText& FallbackText,
    FInteractionActionOption& OutOption) const
{
    OutOption = FInteractionActionOption();

    if (!SourceAI || !TargetActor || !WantedActionTag.IsValid())
    {
        return false;
    }

    const UWorld* World = GetWorld();
    if (!World) return false;

    UGameInstance* GI = World->GetGameInstance();
    UTraitSubsystem* TraitSub = GI ? GI->GetSubsystem<UTraitSubsystem>() : nullptr;
    if (!TraitSub) return false;

    FGameplayTagContainer TargetTags;
    if (TargetActor->GetClass()->ImplementsInterface(UTraitTargetInterface::StaticClass())) // 判断目标对象是否实现了 TraitTargetInterface 接口
    {
        TargetTags = ITraitTargetInterface::Execute_GetInteractionTargetTags(TargetActor);  //调取接口方法，获取Tag
    }
    else if (const UInteractionTargetComponent* TargetComp = TargetActor->FindComponentByClass<UInteractionTargetComponent>())  // 没有则获取InteractionTargetComponent
    {
        TargetTags = TargetComp->GetInteractionTargetTags();    //获取Tag
    }
    
    const ETraitInteractionType WantedType =
        Cast<AEnemyBase>(TargetActor) ? ETraitInteractionType::AI_With_AI : ETraitInteractionType::AI_With_Object;

    TArray<UTraitDefinition*> TraitDefs;
    TraitSub->ResolveTraitDefs(SourceAI->TraitTags, TraitDefs); // 高优先级在前

    // 遍历特质定义，获取符合当前行为Tag的配置值
    for (const UTraitDefinition* Def : TraitDefs)
    {
        if (!Def) continue;

        for (const FTraitInteractionRule& Rule : Def->Rules)
        {
            if (Rule.InteractionType != WantedType) continue;

            const bool bPassTargetFilter = Rule.TargetTagsAny.IsEmpty() || TargetTags.HasAny(Rule.TargetTagsAny);
            if (!bPassTargetFilter) continue;

            const FGameplayTag RuleActionTag =
                Rule.InteractionActionTag.IsValid() ? Rule.InteractionActionTag : Rule.SuggestedBehaviorTag;

            if (!RuleActionTag.IsValid() || !RuleActionTag.MatchesTagExact(WantedActionTag))
            {
                continue;
            }

            const FTraitResolvedAction Resolved = UTraitActionResolver::ResolveAction(Rule, TraitActionProfile);
            if (!Resolved.bValid || !Resolved.ActionTag.IsValid())
            {
                continue;
            }

            OutOption.ButtonText = Resolved.ButtonText.IsEmpty() ? FallbackText : Resolved.ButtonText;
            OutOption.Spec.ActionTag = Resolved.ActionTag;
            OutOption.Spec.EnergyCost = FMath::Max(0.0f, Resolved.EnergyCost);
            OutOption.Spec.ExecutionRadius = FMath::Max(0.0f, Resolved.ExecutionRadius);
            OutOption.Spec.Duration = FMath::Max(0.0f, Resolved.Duration);

            return OutOption.Spec.IsValid();
        }
    }
    return false;
}

// 若满足“易怒+概率”，把聊天行为改成斗殴
bool AInvisiblePlayerController::TryOverrideChatOptionToBrawl(
    AEnemyBase* SourceAI,
    AActor* TargetActor,
    FInteractionActionOption& InOutOption) const
{
    if (!bEnableIrritableChatToBrawl || !SourceAI || !TargetActor)
    {
        return false;
    }
    
    if (!IrritableTraitTag.IsValid() || !ChatBehaviorRootTag.IsValid() || !BrawlBehaviorTag.IsValid())
    {
        return false;
    }

    if (!IsChatEntryAction(InOutOption.Spec.ActionTag))
    {
        return false;
    }

    if (!SourceAI->TraitTags.HasTagExact(IrritableTraitTag))
    {
        return false;
    }

    // 获取设定概率并进行概率判断
    const float Chance = FMath::Clamp(ChatToBrawlProbability, 0.0f, 1.0f);
    if (Chance <= 0.0f) return false;

    const float Roll = FMath::FRand();
    if (Roll > Chance)
    {
        return false;
    }

    FInteractionActionOption FinalBrawl;
    const FText FallbackText = InOutOption.ButtonText;

    // 先走 Trait 规则解算最终值
    if (TryResolveFinalOptionFromTraitRules(SourceAI, TargetActor, BrawlBehaviorTag, FallbackText, FinalBrawl))
    {
        InOutOption = FinalBrawl;
        UE_LOG(LogTemp, Log, TEXT("[Interaction] 聊天->斗殴 (规则解算) Source=%s Target=%s Roll=%.3f Chance=%.3f"),
            *GetNameSafe(SourceAI), *GetNameSafe(TargetActor), Roll, Chance);
        return true;
    }

    // 若找不到最终值，回退 ActionProfile 默认
    if (TryBuildOptionFromActionProfile(BrawlBehaviorTag, FallbackText, FinalBrawl))
    {
        InOutOption = FinalBrawl;
        UE_LOG(LogTemp, Log, TEXT("[Interaction] 聊天->斗殴 (回退默认) Source=%s Target=%s Roll=%.3f Chance=%.3f"),
            *GetNameSafe(SourceAI), *GetNameSafe(TargetActor), Roll, Chance);
        return true;
    }

    // 最后兜底：仅换Tag，其余沿用原聊天数值
    InOutOption.Spec.ActionTag = BrawlBehaviorTag;
    UE_LOG(LogTemp, Warning, TEXT("[Interaction] 聊天->斗殴 (仅更换Tag) Source=%s Target=%s"),
        *GetNameSafe(SourceAI), *GetNameSafe(TargetActor));
    return true;
}

// 输出最终执行行为，并加锁
bool AInvisiblePlayerController::TryResolveLockedOrNewPairDecision(
    AEnemyBase* SourceAI,
    AActor* TargetActor,
    const FInteractionActionOption& ClickedOption,
    FInteractionActionOption& OutFinalOption,
    bool& bOutShouldCreatePairLock) const
{
    OutFinalOption = ClickedOption;
    bOutShouldCreatePairLock = false;

    if (!SourceAI || !TargetActor || !ClickedOption.Spec.ActionTag.IsValid())
    {
        return false;
    }

    // 已有 Pair 锁：强制复用锁定行为
    if (const FInteractionPairDecisionLock* Existing = FindPairDecisionLock(SourceAI, TargetActor))
    {
        if (Existing->bActive && Existing->LockedOption.Spec.IsValid())
        {
            OutFinalOption = Existing->LockedOption;
            return true;
        }
    }

    // 无锁时，仅“聊天入口”参与首次锁定
    if (!IsChatEntryAction(ClickedOption.Spec.ActionTag))
    {
        return true;
    }

    // 首次判定：可能替换为斗殴，也可能保持聊天
    FInteractionActionOption FinalOption = ClickedOption;
    TryOverrideChatOptionToBrawl(SourceAI, TargetActor, FinalOption);

    // 首次结果写入 Pair 锁（无论最终是聊天还是斗殴）
    // SetPairDecisionLock(SourceAI, TargetActor, FinalOption);

    // 不在此处上锁，防止出现能量计算问题
    bOutShouldCreatePairLock = true;
    OutFinalOption = FinalOption;
    return true;
}

// 注册ai事件结束委托
void AInvisiblePlayerController::RegisterEnemyInteractionResolvedDelegates()
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);

    for (AActor* Actor : FoundEnemies)
    {
        APawn* EnemyPawn = Cast<APawn>(Actor);
        if (!EnemyPawn) continue;

        AEnemyAIController* Ctrl = Cast<AEnemyAIController>(EnemyPawn->GetController());
        if (!Ctrl) continue;

        Ctrl->OnInteractionResolvedNative.RemoveAll(this);
        Ctrl->OnInteractionResolvedNative.AddUObject(this, &AInvisiblePlayerController::HandleInteractionResolvedFromAI);
    }
}

// 注销ai事件结束委托
void AInvisiblePlayerController::UnregisterEnemyInteractionResolvedDelegates()
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundEnemies);

    for (AActor* Actor : FoundEnemies)
    {
        APawn* EnemyPawn = Cast<APawn>(Actor);
        if (!EnemyPawn) continue;

        AEnemyAIController* Ctrl = Cast<AEnemyAIController>(EnemyPawn->GetController());
        if (!Ctrl) continue;

        Ctrl->OnInteractionResolvedNative.RemoveAll(this);
    }
}

// 处理ai事件结束
void AInvisiblePlayerController::HandleInteractionResolvedFromAI(
    AActor* SourceActor,
    AActor* TargetActor,
    FGameplayTag ActionTag,
    EInteractionEndReason EndReason)
{
    if (!bUnlockPairLockOnInteractionEnd)
    {
        return;
    }
    
    // 结束或中断时解锁
    // if (EndReason == EInteractionEndReason::Completed || EndReason == EInteractionEndReason::Interrupted)
    // 结束时解锁
    if (EndReason == EInteractionEndReason::Completed)
    {
        ClearPairDecisionLock(SourceActor, TargetActor);
    }
}

// 生命周期结束后，解绑ai事件结束委托
void AInvisiblePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UnregisterEnemyInteractionResolvedDelegates();
    UnregisterEnemyInteractionDelegates();
    Super::EndPlay(EndPlayReason);
}


// 计算源AI和目标AI最后交互点
bool AInvisiblePlayerController::BuildExpectedInteractionPointForTargetHold(
    const FLockedAIPath& LockedPath,
    const APawn* SourcePawn,
    const AActor* TargetActor,
    FVector& OutExpectedPoint) const
{
    OutExpectedPoint = FVector::ZeroVector;

    if (!SourcePawn || !TargetActor)
    {
        return false;
    }

    const FVector SourceLoc = SourcePawn->GetActorLocation();

    // 获取目标AI中心坐标
    FVector BoundsOrigin = FVector::ZeroVector;
    FVector BoundsExtent = FVector::ZeroVector;
    TargetActor->GetActorBounds(true, BoundsOrigin, BoundsExtent);

    // 坐标二维化
    const FVector2D C(BoundsOrigin.X, BoundsOrigin.Y);
    // 交互半径
    const float R = FMath::Max(10.0f, LockedPath.ConfirmedExecutionRadius);
    // 在交互半径内的容忍距离
    const float InRangeTolerance = 5.0f;
    // 源AI坐标二维化
    const FVector2D SourceXY(SourceLoc.X, SourceLoc.Y);
    // 源AI到目标AI中心的距离
    const float DistSourceToCenter = FVector2D::Distance(SourceXY, C);

    // 源AI本来就在交互半径内：直接用当前位置
    if (DistSourceToCenter <= (R + InRangeTolerance))
    {
        OutExpectedPoint = SourceLoc;
        return true;
    }

    // 源AI不在交互半径内：末端路径线段与交互范围圆求交点
    if (LockedPath.Points.Num() >= 2)
    {
        const FVector PPrev3D = LockedPath.Points[LockedPath.Points.Num() - 2];
        const FVector PLast3D = LockedPath.Points[LockedPath.Points.Num() - 1];
        
        const FVector2D A(PPrev3D.X, PPrev3D.Y);
        const FVector2D B(PLast3D.X, PLast3D.Y);
        const FVector2D D = B - A;
        const FVector2D F = A - C;

        const float a = FVector2D::DotProduct(D, D);
        const float b = 2.0f * FVector2D::DotProduct(F, D);
        const float c = FVector2D::DotProduct(F, F) - R * R;

        if (a > KINDA_SMALL_NUMBER)
        {
            const float Discriminant = b * b - 4.0f * a * c;

            if (Discriminant >= 0.0f)
            {
                const float SqrtD = FMath::Sqrt(Discriminant);
                const float Inv2A = 1.0f / (2.0f * a);
                const float T1 = (-b - SqrtD) * Inv2A;
                const float T2 = (-b + SqrtD) * Inv2A;

                bool bHasCandidate = false;
                float BestT = -1.0f;

                auto TryPickT = [&](float T)
                {
                    if (T >= 0.0f && T <= 1.0f)
                    {
                        // 取更靠近末端B的交点，更符合“接近完成时站位”
                        if (!bHasCandidate || T > BestT)
                        {
                            bHasCandidate = true;
                            BestT = T;
                        }
                    }
                };

                TryPickT(T1);
                TryPickT(T2);

                if (bHasCandidate)
                {
                    const FVector2D HitXY = A + D * BestT;
                    const float HitZ = FMath::Lerp(PPrev3D.Z, PLast3D.Z, BestT);
                    OutExpectedPoint = FVector(HitXY.X, HitXY.Y, HitZ);
                    return true;
                }
            }
        }
    }


    // 若源AI路径只有一个点，则按 ExecutionRadius 反推
    FVector2D Dir = (C - SourceXY).GetSafeNormal();

    // 若Source->Target方向退化，尝试用末段方向
    if (Dir.IsNearlyZero() && LockedPath.Points.Num() >= 2)
    {
        const FVector2D A(LockedPath.Points[LockedPath.Points.Num() - 2].X, LockedPath.Points[LockedPath.Points.Num() - 2].Y);
        const FVector2D B(LockedPath.Points[LockedPath.Points.Num() - 1].X, LockedPath.Points[LockedPath.Points.Num() - 1].Y);
        Dir = (B - A).GetSafeNormal();
    }

    if (Dir.IsNearlyZero())
    {
        OutExpectedPoint = SourceLoc;
        return true;
    }

    const FVector2D FallbackXY = C - Dir * R;
    OutExpectedPoint = FVector(FallbackXY.X, FallbackXY.Y, SourceLoc.Z);
    return true;
    
}


// ===== 游戏结束功能 =====
// 设置游戏输入锁定
void AInvisiblePlayerController::SetGameplayInputLocked(bool bLocked)
{
    if (bGameplayInputLocked == bLocked)
	{
		return;
	}

    bGameplayInputLocked = bLocked;

    SetIgnoreMoveInput(bLocked);
    SetIgnoreLookInput(bLocked);

    if(!bLocked)
    {
        return;
    }

    // 清除所有输入状态
    bIsRunning = false;
    bRotateHeld = false;
	bEditRotateHeld = false;
	EditPanInput = FVector2D::ZeroVector;

    // 清理路径预览
    bPathDragActive = false;
	DragPawn.Reset();
	bHasPreviewPath = false;
	PreviewTarget = FVector::ZeroVector;
	PreviewPathPoints.Reset();

    ClearPreviewInteraction();

    // 隐藏所有交互按钮
    HideAllInteractionButtons();
	HideAIInfoPanel();
	StopEnergyRegen();

    if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		PlayerCharacter->bIsRunning = false;
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->NormalWalkSpeed;
		PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
	}
}