// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/EditModeCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h" 
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

// Sets default values
AEditModeCamera::AEditModeCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// 编辑模式相机不进行Tick更新,逻辑由PlayerController控制

	// 根节点
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// 相机旋转圆心
	CameraPivot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPivot"));
	CameraPivot->SetupAttachment(RootComponent);
	CameraPivot->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));


	// 弹簧臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(CameraPivot);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = false;



	// 以SceneComponent为根节点
	// USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// RootComponent = Root;

	// 相机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// 鼠标地面指示器 Niagara 组件
	GroundRingNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GroundRingNiagara"));
	GroundRingNiagara->SetupAttachment(RootComponent);
	GroundRingNiagara->SetAutoActivate(false);
	GroundRingNiagara->SetVisibility(false);

}

// Called when the game starts or when spawned
void AEditModeCamera::BeginPlay()
{
	Super::BeginPlay();

	// 指示器与 Niagara 系统绑定
	if (GroundRingNiagara && GroundRingNiagaraSystem)
	{
		GroundRingNiagara->SetAsset(GroundRingNiagaraSystem);
	}

	ApplyRotation();
}

// Called every frame
void AEditModeCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 初始化朝向（新版，不改变位置）
void AEditModeCamera::InitializeCamera(float InitialYaw)
{
	CurrentYaw = InitialYaw;
	// SetActorLocation(Location);
	ApplyRotation();
}

// 相机平移
void AEditModeCamera::PanCamera(const FVector2D& InputAxis, float DeltaTime)
{
	// 相机移动逻辑，与角色相同
	const FRotator YawRot(0.0f, CurrentYaw, 0.0f);
	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	const FVector MoveDir = (Forward * InputAxis.Y + Right * InputAxis.X) * CameraPanSpeed * DeltaTime;

	AddActorWorldOffset(MoveDir);
}

// 相机旋转
void AEditModeCamera::OrbitCamera(float DeltaYaw)
{
	CurrentYaw += DeltaYaw;
	ApplyRotation();
}

// 更新鼠标投影指示器（仅投影到地面）
void AEditModeCamera::UpdateGroundRing(APlayerController* PC)
{
	if (!PC || !GroundRingNiagara)
	{
		return;
	}

	// 未配置 Niagara 资源时保持隐藏，避免空资源状态下反复激活/停用
	if (!GroundRingNiagaraSystem)
	{
		GroundRingNiagara->SetVisibility(false);
		GroundRingNiagara->Deactivate();
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// 鼠标 → 世界射线
	FVector WorldOrigin;
	FVector WorldDirection;
	if (!PC->DeprojectMousePositionToWorld(WorldOrigin, WorldDirection))
	{
		GroundRingNiagara->SetVisibility(false);
		GroundRingNiagara->Deactivate();
		return;
	}

	constexpr float TraceLength = 100000.0f;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(EditModeCursorTrace), /*bTraceComplex*/ false, this);
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	if (!World->LineTraceSingleByChannel(Hit, WorldOrigin, WorldOrigin + WorldDirection * TraceLength, ECC_Visibility, Params))
	{
		GroundRingNiagara->SetVisibility(false);
		GroundRingNiagara->Deactivate();
		return;
	}

	// 只处理法线朝上的水平面（ImpactNormal.Z > 0.7 ≈ 倾斜角 < 45°）
	if (Hit.ImpactNormal.Z < 0.7f)
	{
		GroundRingNiagara->SetVisibility(false);
		GroundRingNiagara->Deactivate();
		return;
	}

	// Niagara 指示器：对齐地面法线并放置到命中点
	const FRotator GroundEffectRotation = UKismetMathLibrary::MakeRotFromZ(Hit.ImpactNormal);

	GroundRingNiagara->SetWorldLocation(Hit.ImpactPoint);
	GroundRingNiagara->SetWorldRotation(GroundEffectRotation);
	GroundRingNiagara->SetVisibility(true);
	if (!GroundRingNiagara->IsActive())
	{
		GroundRingNiagara->Activate(true);
	}
}

// 应用旋转
void AEditModeCamera::ApplyRotation()
{
	// SetActorRotation(FRotator(CameraPitch, CurrentYaw, 0.0f));
	if(CameraPivot)
	{
		CameraPivot->SetWorldRotation(FRotator(0.0f, CurrentYaw, 0.0f));
	}
	if(CameraBoom)
	{
		FRotator BoomRot = CameraBoom->GetRelativeRotation();
		BoomRot.Pitch = CameraPitch;
		CameraBoom->SetRelativeRotation(BoomRot);
	}
}
