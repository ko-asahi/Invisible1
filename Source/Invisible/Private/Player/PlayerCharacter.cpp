// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/EnemyAIController.h"
#include "InvisibleGameStateBase.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"
#include "Data/SIZZ_CustomIndicatorRefreshValue.h"
#include "Data/SIZZ_IndicatorBehaviourDefinition.h"
#include "Decals/SIZZ_DecalBaseActor.h"
#include "SpellIndicatorLibrary/SIZZ_SpellIndicatorLibrary.h"

namespace
{
bool IsSafeCircleDefinition(const USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition)
{
	return IndicatorDefinition
		&& IndicatorDefinition->IndicatorClassToSpawn
		&& IndicatorDefinition->IndicatorMaterial
		&& IndicatorDefinition->IndicatorAnimationCurve
		&& IndicatorDefinition->RefreshData
		&& IndicatorDefinition->RefreshData->RefreshValue > 0.0f;
}

ASIZZ_DecalBaseActor* SpawnIndicatorCircleByReflection(
	UObject* WorldObjContext,
	USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition,
	const FVector& Position,
	float Time,
	float Radius)
{
	UClass* LibraryClass = USIZZ_SpellIndicatorLibrary::StaticClass();
	if (!LibraryClass)
	{
		return nullptr;
	}

	UFunction* SpawnFunc = LibraryClass->FindFunctionByName(TEXT("SpawnIndicatorCircle"));
	if (!SpawnFunc)
	{
		return nullptr;
	}

	struct FSpawnIndicatorCircleParams
	{
		UObject* WorldObjContext = nullptr;
		USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition = nullptr;
		FVector Position = FVector::ZeroVector;
		float Time = 1.0f;
		float Radius = 100.0f;
		ASIZZ_DecalBaseActor* ReturnValue = nullptr;
	};

	FSpawnIndicatorCircleParams Params;
	Params.WorldObjContext = WorldObjContext;
	Params.IndicatorDefinition = IndicatorDefinition;
	Params.Position = Position;
	Params.Time = Time;
	Params.Radius = Radius;

	UObject* LibraryCDO = LibraryClass->GetDefaultObject();
	if (!LibraryCDO)
	{
		return nullptr;
	}

	LibraryCDO->ProcessEvent(SpawnFunc, &Params);
	return Params.ReturnValue;
}
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 弹簧臂旋转圆心
	CameraPivot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPivot"));
	CameraPivot->SetupAttachment(RootComponent);
	CameraPivot->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));

	// 相机旋转半径（弹簧臂）
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(CameraPivot);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	// 玩家跟随摄像机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	// 噪声圈贴花组件
	NoiseRingDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("NoiseRingDecal"));
	NoiseRingDecal->SetupAttachment(RootComponent);
	NoiseRingDecal->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	NoiseRingDecal->SetVisibility(false);
	NoiseRingDecal->DecalSize = FVector(NoiseRingProjectionDepth, 100.0f, 100.0f);

	// 关闭自动转向移动方向，手动控制角色方向
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	// 初始化角色旋转最大速度
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1080.0f, 0.0f);

	// 允许角色蹲下
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
    
	// 设置蹲下时的移动速度
    GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchWalkSpeed;
    
	// 设置正常时的移动速度
    GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;

	// 显式注册为听觉刺激源，提升听觉事件在感知系统中的可达性
	HearingStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("HearingStimuliSourceComp"));
	HearingStimuliSourceComp->RegisterForSense(UAISense_Hearing::StaticClass());

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraWorldYaw = GetActorRotation().Yaw; // 与角色初始朝向对齐


	// 缓存Tag
	Tag_Idle = FGameplayTag::RequestGameplayTag(FName("State.Movement.Idle"));
	Tag_Walk = FGameplayTag::RequestGameplayTag(FName("State.Movement.Walk"));
	Tag_CrouchIdle = FGameplayTag::RequestGameplayTag(FName("State.Movement.CrouchIdle"));
	Tag_CrouchWalk = FGameplayTag::RequestGameplayTag(FName("State.Movement.CrouchWalk"));
	Tag_Run = FGameplayTag::RequestGameplayTag(FName("State.Movement.Run"));


	// 初始化角色Tag
	MovementStateTags.AddTag(Tag_Idle);

	if(NoiseRingMaterialBase && NoiseRingDecal)
	{
		
		NoiseRingMID = UMaterialInstanceDynamic::Create(NoiseRingMaterialBase, this);	// 设置动态材质
		NoiseRingDecal->SetDecalMaterial(NoiseRingMID);	// 设置声音圈材质

		// 声音圈渲染范围参数
		NoiseRingMID->SetVectorParameterValue(TEXT("PlayAreaMinWS"), FLinearColor(PlayAreaMinWS.X, PlayAreaMinWS.Y, 0, 0));
        NoiseRingMID->SetVectorParameterValue(TEXT("PlayAreaSizeWS"), FLinearColor(PlayAreaSizeWS.X, PlayAreaSizeWS.Y, 0, 0));
	}

	if (AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
	{
		CachedGlobalHearingRange = GS->GetGlobalHearingRange();
		if (!GS->OnGlobalHearingRangeChanged.IsAlreadyBound(this, &APlayerCharacter::HandleGlobalHearingRangeChanged))
		{
			GS->OnGlobalHearingRangeChanged.AddDynamic(this, &APlayerCharacter::HandleGlobalHearingRangeChanged);
		}
	}

	if (HearingStimuliSourceComp)
	{
		HearingStimuliSourceComp->RegisterWithPerceptionSystem();
	}
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (AInvisibleGameStateBase* GS = World->GetGameState<AInvisibleGameStateBase>())
		{
			GS->OnGlobalHearingRangeChanged.RemoveDynamic(this, &APlayerCharacter::HandleGlobalHearingRangeChanged);
		}
	}

	if (IsValid(ActiveNoiseCircleIndicator))
	{
		ActiveNoiseCircleIndicator->Destroy();
		ActiveNoiseCircleIndicator = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 每帧强制相机Pivot保持目标世界Yaw，不受角色旋转影响
    CameraPivot->SetWorldRotation(FRotator(0.0f, CameraWorldYaw, 0.0f));

	//UE_LOG(LogTemp, Log, TEXT("玩家全局听觉范围: %f"), CachedGlobalHearingRange);
	// 更新角色Tag
	UpdateMovementStateTags();

	// ===== 脚步声上报 =====
    ReportFootstepNoise(DeltaTime);
	UpdateSizzNoiseIndicatorFollow();

	// 声音圈更新
	UpdateNoiseRingVisual(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::OrbitCamera(float DeltaYaw)
{
	CameraWorldYaw += DeltaYaw;
	CameraPivot->SetWorldRotation(FRotator(0.0f, CameraWorldYaw, 0.0f));
}

float APlayerCharacter::GetCameraYaw() const
{
	return CameraWorldYaw;
}


void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    UpdateMovementStateTags();
}

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    UpdateMovementStateTags();
}

void APlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
    UpdateMovementStateTags();
}

void APlayerCharacter::HandleGlobalHearingRangeChanged(float NewRange)
{
	CachedGlobalHearingRange = FMath::Max(0.0f, NewRange);
	
}



void APlayerCharacter::UpdateMovementStateTags()
{
	const float Speed = GetCharacterMovement()->Velocity.Size2D();
	const bool bIsMoving = Speed > MinMovementSpeed;

	FGameplayTag CurrentTag;

	// 玩家Tag赋予
	if(bIsCrouched)
	{
		if(bIsMoving)
		{
			CurrentTag = Tag_CrouchWalk;
		}
		else
		{
			CurrentTag = Tag_CrouchIdle;
		}
	}
	else if(bIsRunning && bIsMoving)
	{
		CurrentTag = Tag_Run;
	}
	else
	{
		if(bIsMoving)
		{
			CurrentTag = Tag_Walk;
		}
		else
		{
			CurrentTag = Tag_Idle;
		}
	}


	// 状态变化时更新角色Tag
	if(!MovementStateTags.HasTagExact(CurrentTag))
	{
		MovementStateTags.Reset();
		MovementStateTags.AddTag(CurrentTag);


		// 打印角色Tag（用于调试）
		FString TagStr = MovementStateTags.ToStringSimple();
		UE_LOG(LogTemp, Log, TEXT("角色Tag: %s"), *TagStr);
	}

	
}

// ===== 角色声音系统 =====

// 通过Tag获取噪声圈参数
bool APlayerCharacter::ResolveNoiseProfileByTag(FNoiseProfile& OutProfile) const
{
    OutProfile = FNoiseProfile{};

    if (MovementStateTags.HasTagExact(Tag_Run))
    {
        OutProfile.bShowRing = true;
        OutProfile.bEmitNoise = true;
        OutProfile.Loudness = RunFootstepLoudness;
        OutProfile.Interval = RunFootstepFrequency;
        return true;
    }

    if (MovementStateTags.HasTagExact(Tag_Walk))
    {
        OutProfile.bShowRing = true;
        OutProfile.bEmitNoise = true;
        OutProfile.Loudness = WalkFootstepLoudness;
        OutProfile.Interval = WalkFootstepFrequency;
        return true;
    }

    if (MovementStateTags.HasTagExact(Tag_CrouchWalk))
    {
        OutProfile.bShowRing = true;     
        OutProfile.bEmitNoise = true;    
        OutProfile.Loudness = CrouchFootstepLoudness;
        OutProfile.Interval = CrouchFootstepFrequency;
        return true;
    }

    // Idle / CrouchIdle
    return false;
}

// 上报脚步声声音事件
void APlayerCharacter::ReportFootstepNoise(float DeltaTime)
{
	// 移动时产生脚步声
	const float Speed = GetCharacterMovement()->Velocity.Size2D();
	if(Speed < MinMovementSpeed) return;

	FNoiseProfile NoiseProfile;
	if(!ResolveNoiseProfileByTag(NoiseProfile) || !NoiseProfile.bEmitNoise) return;

	FootstepTimer -= DeltaTime;
    if (FootstepTimer > 0.f) return;
    FootstepTimer = NoiseProfile.Interval;

	// 上报噪音事件
	FVector FootLocation = GetActorLocation();
    FootLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	DrawHearingRange(NoiseProfile.Loudness, NoiseProfile.Interval);

	if (CachedGlobalHearingRange <= 0.0f) return;
	const float EffectiveRadius = CachedGlobalHearingRange * NoiseProfile.Loudness;
	SpawnSizzNoiseIndicator(EffectiveRadius, NoiseCircleIndicatorDuration > 0.0f ? NoiseCircleIndicatorDuration : NoiseProfile.Interval);

	UAISense_Hearing::ReportNoiseEvent(
		GetWorld(),
		FootLocation,
		NoiseProfile.Loudness,
		this,
		CachedGlobalHearingRange,
		FName("State.Movement.Footstep")
	);
}

void APlayerCharacter::SpawnSizzNoiseIndicator(float EffectiveRadius, float Duration)
{
	if (!bEnableSizzNoiseIndicator)
	{
		return;
	}

	if (!IsSafeCircleDefinition(NoiseCircleIndicatorDefinition))
	{
		return;
	}

	if (EffectiveRadius <= 0.0f)
	{
		return;
	}

	if (IsValid(ActiveNoiseCircleIndicator))
	{
		ActiveNoiseCircleIndicator->Destroy();
		ActiveNoiseCircleIndicator = nullptr;
	}

	const float SafeDuration = FMath::Max(Duration, 0.05f);
	const float ScaledRadius = FMath::Max(EffectiveRadius * FMath::Max(NoiseCircleRadiusScale, 0.1f), 1.0f);
	FVector FootLocation = GetActorLocation();
	FootLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	ActiveNoiseCircleIndicator = SpawnIndicatorCircleByReflection(
		this,
		NoiseCircleIndicatorDefinition,
		FootLocation,
		SafeDuration,
		ScaledRadius);
}

void APlayerCharacter::UpdateSizzNoiseIndicatorFollow() const
{
	if (!IsValid(ActiveNoiseCircleIndicator))
	{
		return;
	}

	FVector FootLocation = GetActorLocation();
	FootLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	ActiveNoiseCircleIndicator->SetActorLocation(FootLocation);
}


// 绘制听觉范围
void APlayerCharacter::DrawHearingRange(float Loudness, float Duration)
{
	const FVector PlayerLoc = GetActorLocation();

	for (TActorIterator<AEnemyAIController> It(GetWorld()); It; ++It)
	{
		AEnemyAIController* AI = *It;
		APawn* EnemyPawn = AI->GetPawn();
		if (!EnemyPawn) continue;

		const FVector EnemyLoc = EnemyPawn->GetActorLocation();
		const float Hearing = AI->GetHearingRange(); // ai听觉范围
		const float Effective = Hearing * Loudness;
		const float Dist = FVector::Dist2D(PlayerLoc, EnemyLoc);

		const bool bCanHear = Dist <= Effective;
		const FColor C = bCanHear ? FColor::Green : FColor::Red;

		//DrawDebugCircle(GetWorld(), EnemyLoc + FVector(0,0,5.0f), Hearing, 48, FColor::Silver, false, 0.1f, 0, 1.2f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f));
		//DrawDebugCircle(GetWorld(), EnemyLoc + FVector(0,0,5.0f), Effective, 48, C, false, 0.15f, 0, 2.5f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f));
		DrawDebugCircle(GetWorld(), GetActorLocation(), Effective, 64, C, false, 0.15f, 0, 2.f, FVector(1,0,0), FVector(0,1,0), false);


		if (bCanHear)
		{
			DrawDebugLine(GetWorld(), EnemyLoc + FVector(0,0,40), PlayerLoc + FVector(0,0,40), FColor::Green, false, 0.12f, 0, 1.5f);
		}
	}
}

// ===== 噪声圈效果实现 =====

// 显示噪声圈
void APlayerCharacter::ShowNoiseRing(float EffectiveRadius, float Duration)
{
	if(!NoiseRingMID || !NoiseRingDecal) return;

	const FVector FootPos = GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 3.0f);


	// 更新噪声圈贴花组件参数
	NoiseRingDecal->SetWorldLocation(FootPos);
	NoiseRingDecal->DecalSize = FVector(NoiseRingProjectionDepth, EffectiveRadius, EffectiveRadius);
	NoiseRingDecal->SetVisibility(true);

	// 更新噪声圈动态材质参数
	NoiseRingMID->SetVectorParameterValue(TEXT("RingCenterWS"), FLinearColor(FootPos.X, FootPos.Y, FootPos.Z, 0));
	NoiseRingMID->SetScalarParameterValue(TEXT("RingRadius"), EffectiveRadius);
	NoiseRingMID->SetScalarParameterValue(TEXT("RingOpacity"), 1.0f);

	NoiseRingTimeLeft = Duration;
	NoiseRingTotalTime = FMath::Max(0.01f, Duration);
}


// 更新噪声圈
void APlayerCharacter::UpdateNoiseRingVisual(float DeltaTime)
{
    if (!NoiseRingDecal || !NoiseRingMID) return;

    FNoiseProfile P;
    const bool bHasProfile = ResolveNoiseProfileByTag(P);

    float HearingRangeRef = 1500.f;
    if (const AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
    {
        HearingRangeRef = GS->GetGlobalHearingRange();
    }

	// 计算目标半径和透明度
    const float TargetRadius = HearingRangeRef * P.Loudness;
    const float TargetOpacity = (bHasProfile && P.bShowRing) ? 1.0f : 0.0f;

    // 每帧跟随玩家脚底
    const FVector FootPos = GetActorLocation() -
        FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 3.0f);
    NoiseRingDecal->SetWorldLocation(FootPos);

    // 半径随状态平滑变化（避免跑/走切换突变）
    CurrentRingRadius = FMath::FInterpTo(CurrentRingRadius, TargetRadius, DeltaTime, 12.f);
    CurrentRingOpacity = FMath::FInterpTo(CurrentRingOpacity, TargetOpacity, DeltaTime, 14.f);

    const bool bVisible = CurrentRingOpacity > 0.02f;
    NoiseRingDecal->SetVisibility(bVisible);

    if (!bVisible) return;

    // 更新噪声圈贴花组件参数
    NoiseRingDecal->DecalSize = FVector(NoiseRingProjectionDepth, CurrentRingRadius, CurrentRingRadius);
    NoiseRingMID->SetVectorParameterValue(TEXT("RingCenterWS"), FLinearColor(FootPos.X, FootPos.Y, FootPos.Z, 0));
    NoiseRingMID->SetScalarParameterValue(TEXT("RingRadius"), CurrentRingRadius);
    NoiseRingMID->SetScalarParameterValue(TEXT("RingOpacity"), CurrentRingOpacity);
}