// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/EditModeCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AEditModeCamera::AEditModeCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// 编辑模式相机不进行Tick更新,逻辑由PlayerController控制

	// 以SceneComponent为根节点
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// 相机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	// 鼠标投影指示器组件
	GroundRingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundRingMesh"));
	GroundRingMesh->SetupAttachment(RootComponent);
	GroundRingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GroundRingMesh->SetVisibility(false);

}

// Called when the game starts or when spawned
void AEditModeCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEditModeCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 初始化位置与朝向
void AEditModeCamera::InitializeCamera(const FVector& Location, float InitialYaw)
{
	CurrentYaw = InitialYaw;
	SetActorLocation(Location);
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

// 更新鼠标投影指示器
void AEditModeCamera::UpdateGroundRing(APlayerController* PC)
{
	if(!PC) return;

	// 获取鼠标世界位置
	FHitResult HitResult;

	if(PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		GroundRingMesh->SetWorldLocation(HitResult.Location + FVector(0.0f, 0.0f, 2.0f));
		GroundRingMesh->SetVisibility(true);
	}
	else
	{
		GroundRingMesh->SetVisibility(false);
	}
}

// 应用旋转
void AEditModeCamera::ApplyRotation()
{
	SetActorRotation(FRotator(CameraPitch, CurrentYaw, 0.0f));
}