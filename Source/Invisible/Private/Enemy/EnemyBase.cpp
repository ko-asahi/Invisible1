// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/PatrolPath.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/WidgetComponent.h>


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 绑定 AI Controller
	AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 设置角色的转身速度
	bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);

	AlertBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AlertBarWidgetComp"));
	AlertBarWidgetComp->SetupAttachment(GetMesh());
	AlertBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 屏幕空间更清晰
	AlertBarWidgetComp->SetDrawSize(FVector2D(120.f, 16.f));
	AlertBarWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 220.f));

	AlertBarWidgetComp->SetDrawAtDesiredSize(true);      // 跟随Widget实际尺寸
	AlertBarWidgetComp->SetPivot(FVector2D(0.5f, 1.0f)); // 底边中心对齐到头顶点
	AlertBarWidgetComp->SetVisibility(false);             // 默认隐藏，警戒>0再显示
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 获取下一个巡逻点
AActor* AEnemyBase::GetNextPatrolPoint()
{
	if (!AssignedPatrolPath) return nullptr;

	return AssignedPatrolPath->GetWaypoint(CurrentPatrolPointIndex);
}



