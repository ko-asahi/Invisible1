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
    bIsEditMode = !bIsEditMode;

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
        EditCamera = GetWorld()->SpawnActor<AEditModeCamera>(EditModeCameraClass, CamLoc, FRotator::ZeroRotator);


        if(EditCamera)
        {
            // 初始化相机位置与朝向(朝向由EditModeCamera内参数CameraPitch控制)
            EditCamera->InitializeCamera(CamLoc, CamRot.Yaw);

            // 平滑过渡到当前视角
            //SetViewTargetWithBlend(EditCamera,EditModeCameraTransitionSpeed);

            // 立即切换视角
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

        UE_LOG(LogTemp, Log, TEXT("切换为编辑模式"));
    }

    if(!bIsEditMode)
    {
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
                        EnemyAI->SetInjectedPath(LockedAIPaths[LockedIndex].Points);
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
    bRotateHeld = true;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转启动"));
}

// 旋转状态结束
void AInvisiblePlayerController::OnRotateHoldCompleted()
{
    bRotateHeld = false;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转结束"));
}

// 相机旋转
void AInvisiblePlayerController::OnRotate(const FInputActionValue& Value)
{
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
    if(!bIsEditMode) return;
    EditPanInput = Value.Get<FVector2D>();
}

// 按键松开时清零输入
void AInvisiblePlayerController::OnEditPanCompleted()
{
    EditPanInput = FVector2D::ZeroVector;
}

// 旋转状态触发
void AInvisiblePlayerController::OnEditRotateHoldStarted()
{
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
    if(!bIsEditMode) return;
    bEditRotateHeld = false;

    //bShowMouseCursor = true;

    UE_LOG(LogTemp, Log, TEXT("镜头旋转结束"));
}

// 旋转输入
void AInvisiblePlayerController::OnEditRotate(const FInputActionValue& Value)
{
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
    if(!bIsEditMode || bEditRotateHeld) return;
    
    // 重置状态
    bPathDragActive = false;
    DragPawn.Reset();

    bHasPreviewPath = false;
    PreviewTarget = FVector::ZeroVector;
    PreviewPathPoints.Reset();
    PreviewPathLength = 0.0f;
    PreviewEnergyCost = 0.0f;
    DragPawnOldPathCost = 0.0f;

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
    UE_LOG(LogTemp, Log, TEXT("选中Actor: %s"), *SelectedActor->GetName());
}

// 拖拽时更新路径预览
void AInvisiblePlayerController::OnEditPathDragTriggered()
{
    if(!bIsEditMode || !bPathDragActive || !DragPawn.IsValid()) return;

    FHitResult GroundHit;
    if(!GetHitResultUnderCursor(ECC_Visibility, false, GroundHit))
    {
        bHasPreviewPath = false;    // 清除预览路径
        PreviewTarget = FVector::ZeroVector;    // 清除预览目标
        PreviewPathPoints.Reset();    // 清除预览路径点
        PreviewPathLength = 0.0f;    // 清除预览路径长度
        PreviewEnergyCost = 0.0f;    // 清除预览能量消耗
        DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost, 0.f, MaxPathEnergy);    // 刷新当前能量
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
        return;
    }

    bHasPreviewPath = true;
    PreviewPathPoints = MoveTemp(ClampedPoints);
    PreviewTarget = ClampedTarget;
    PreviewPathLength = UsedLength;
    PreviewEnergyCost = UsedLength * CostPerUnit;
     // 实时显示（不真实扣）
     DisplayPathEnergy = FMath::Clamp(CurrentPathEnergy + DragPawnOldPathCost - PreviewEnergyCost, 0.f, MaxPathEnergy);

    UE_LOG(LogTemp, Log, TEXT("路径预览更新"));
}

// 拖拽结束，保留路径直到编辑模式关闭
void AInvisiblePlayerController::OnEditPathDragCompleted()
{
    if(!bIsEditMode) return;

    bPathDragActive = false;

    if(!DragPawn.IsValid() || !bHasPreviewPath || PreviewPathPoints.Num() < 2)
    {
        bHasPreviewPath = false;
        PreviewTarget = FVector::ZeroVector;
        PreviewPathPoints.Reset();
        PreviewPathLength = 0.f;
        PreviewEnergyCost = 0.f;
        DragPawnOldPathCost = 0.f;
        DisplayPathEnergy = CurrentPathEnergy;
        return;
    }

    const APawn* DraggingPawn = DragPawn.Get();
    const int32 Index = FindLockedPathIndexByPawn(DraggingPawn);

    if(Index == INDEX_NONE)
    {
        FLockedAIPath NewPath;
        NewPath.OwnerPawn = DragPawn;
        NewPath.Target = PreviewTarget;
        NewPath.Points = PreviewPathPoints;
        NewPath.PathLength = PreviewPathLength;
        NewPath.EnergyCost = PreviewEnergyCost;
        LockedAIPaths.Add(MoveTemp(NewPath));
    }
    else
    {
        LockedAIPaths[Index].Target = PreviewTarget;
        LockedAIPaths[Index].Points = PreviewPathPoints;
        LockedAIPaths[Index].PathLength = PreviewPathLength;
        LockedAIPaths[Index].EnergyCost = PreviewEnergyCost;
        
    }

    CurrentPathEnergy = FMath::Clamp(CurrentPathEnergy - PreviewEnergyCost, 0.f, MaxPathEnergy);

    bHasPreviewPath = false;
    PreviewTarget = FVector::ZeroVector;
    PreviewPathPoints.Reset();
    PreviewPathLength = 0.0f;
    PreviewEnergyCost = 0.0f;
    DragPawnOldPathCost = 0.0f;
    DisplayPathEnergy = CurrentPathEnergy;

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

// 删除当前选中的ai路径
void AInvisiblePlayerController::OnRemoveSelectedAIPath()
{
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

    AIInfoPanelInstance->UpdateAIInfo(InEnemy->AIInfoData, InEnemy);
    AIInfoPanelInstance->SetVisibility(ESlateVisibility::Visible);

    UE_LOG(LogTemp, Log, TEXT("显示敌方信息面板"));
}

// 隐藏ai单位信息面板
void AInvisiblePlayerController::HideAIInfoPanel()
{
    if(!AIInfoPanelInstance) return;
    AIInfoPanelInstance->SetVisibility(ESlateVisibility::Hidden);
}
