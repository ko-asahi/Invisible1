// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Camera/EditModeCamera.h"
#include "Enemy/AIInfoPanelWidget.h"


#include "InvisiblePlayerController.generated.h"

/**
 * 
 */

// 保存单个ai路径
USTRUCT()
struct FLockedAIPath
{
    GENERATED_BODY()
    TWeakObjectPtr<APawn> OwnerPawn;
    FVector Target = FVector::ZeroVector;
    TArray<FVector> Points;

	float PathLength = 0.0f;	// 路径长度
	float EnergyCost = 0.0f;	// 能量消耗
};

UCLASS()
class INVISIBLE_API AInvisiblePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 增强输入组件

	// 跟随模式增强输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* FollowMappingContext;

	// 编辑模式增强输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* EditModeMappingContext;

	// 切换功能增强输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* SwitchModeMappingContext;

	// 切换输入模式按键
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SwitchModeAction;

	// 编辑模式判定参数(预留，可用于切换时的动画效果)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|IsEditMode")
	bool bIsEditMode = false;



	// =====跟随模式输入=====
	// 移动输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	UInputAction* MoveAction;

	// 旋转输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	UInputAction* RotateAction;

	// 旋转状态按键
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	UInputAction* RotateHoldAction;

	// 蹲下输入按键
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	UInputAction* CrouchAction;

	// 奔跑输入按键（按住时跑）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	UInputAction* RunAction;

	// 当前是否处于奔跑状态
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	bool bIsRunning = false;

	// 旋转灵敏度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	float OrbitYawSpeed = 0.3f;

	// 角色转向速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	float CharacterRotateSpeed = 15.0f;

	// 镜头旋转是否启动
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	bool bRotateHeld = false;

	// 当前是否处于蹲下状态
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|FollowMode")
	bool bIsCrouching = false;



	// =====编辑模式输入=====

	// 移动输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
    UInputAction* EditPanAction; 

	// 旋转输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
    UInputAction* EditRotateAction; 

	// 旋转状态按键
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
    UInputAction* EditRotateHoldAction; 

	// 单位选择按键
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
    UInputAction* EditSelectAction; 

	// 相机过渡速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
	float EditModeCameraTransitionSpeed = 0.3f;

	// 当前选择Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditMode")
	AActor* SelectedActor = nullptr;

	// ===== 编辑模式下“心控”功能输入 =====

	// 拖拽状态
	bool bPathDragActive = false;

	TWeakObjectPtr<APawn> DragPawn;	// 弱引用指针，防止查找不到对象崩溃

	// 当前路径所属ai
	//TWeakObjectPtr<APawn> LockedPathOwner;

	// 当前帧路径预览
	bool bHasPreviewPath = false;
	FVector PreviewTarget = FVector::ZeroVector;
	TArray<FVector> PreviewPathPoints;
	float PreviewPathLength = 0.0f;
	float PreviewEnergyCost = 0.0f;

	// 松开后保留路径
	//bool bHasLockedPath = false;
	//FVector LockedTarget = FVector::ZeroVector;
	//TArray<FVector> LockedPathPoints;

	// 所有ai的已锁定路径
	TArray<FLockedAIPath> LockedAIPaths;

	// 当前拖拽AI旧路径消耗（用于替换与实时显示）
	float DragPawnOldPathCost = 0.0f;

	// UI显示用能量（拖拽中实时变化）
	UPROPERTY(BlueprintReadOnly, Category="EditMode|Energy")
	float DisplayPathEnergy = 0.0f;

	// 低于该值时，不绘制路径
	UPROPERTY(EditAnywhere, Category = "EditMode|Path")
	float MinPathDistance = 100.0f;

	// 绘制高度参数
	UPROPERTY(EditAnywhere, Category="EditMode|Path")
	float PathDebugZOffset = 10.0f;

	// 删除已锁定路径
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|EditMode")
	UInputAction* EditRemovePathAction;

	// 只有鼠标位移超过阈值，才认为是拖拽
	bool bPathActuallyDragged = false;
	FVector2D PathDragStartMousePos = FVector2D::ZeroVector;

	// 当鼠标位移超过该阈值时，视为拖拽
	UPROPERTY(EditAnywhere, Category="EditMode|Path")
	float PathDragPixelThreshold = 6.0f;

	// =====能量机制=====

	// 最大能量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EditMode|Energy")
	float MaxPathEnergy = 1000.0f;

	// 当前能量
	UPROPERTY(BlueprintReadOnly, Category="EditMode|Energy")
	float CurrentPathEnergy = 1000.0f;

	// 每单位的能量消耗（默认 1米 = 1能量）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EditMode|Energy")
	float PathEnergyCostPerUnit = 1.0f;

	// 退出编辑模式后开始回复能量的时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EditMode|Energy")
	float EnergyRegenDelay = 2.0f;

	// 回复能量速率（每秒回复的能量）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EditMode|Energy")
	float EnergyRegenRate = 80.0f;

	// 是否正在回复能量
	UPROPERTY(BlueprintReadOnly, Category="EditMode|Energy")
	bool bIsRegenEnergy = false;

	// 计时器，用于延时回复能量
	FTimerHandle EnergyRegenTimerHandle;

	// ===== ai单位信息显示功能 =====
	
	// ai单位信息显示UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EditMode|AIInfo")
	TSubclassOf<UAIInfoPanelWidget> AIInfoPanelClass;
	
	// ai单位信息显示实例
	UPROPERTY()
	UAIInfoPanelWidget* AIInfoPanelInstance = nullptr;




protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;	// 切换输入模式按键绑定

	void SwitchMode();	// 切换输入模式

	void UpdateInputContext();	// 更新增强输入组件



	// =====跟随模式输入=====
	// 移动输入
	void OnMove(const FInputActionValue& Value);

	// 旋转输入
	void OnRotate(const FInputActionValue& Value);

	// 旋转状态触发
	void OnRotateHoldStarted();

	// 旋转状态结束
	void OnRotateHoldCompleted();

	// 蹲下起立状态切换
	void OnCrouchToggle();

	// 奔跑状态开始
	void OnRunStarted();

	// 奔跑状态结束
	void OnRunCompleted();


	// =====编辑模式输入=====
	// 移动输入
	void OnEditPan(const FInputActionValue& Value);

	// 按键松开时清零输入
	void OnEditPanCompleted();           
	
	// 旋转输入
    void OnEditRotate(const FInputActionValue& Value);

	// 旋转状态触发
    void OnEditRotateHoldStarted();

	// 旋转状态结束
    void OnEditRotateHoldCompleted();

	// 旋转状态
    void OnEditRotateHold();

	// 单位选择
    void OnEditSelect();

	// 可在蓝图中指定具体的 EditModeCamera 蓝图类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditMode")
	TSubclassOf<AEditModeCamera> EditModeCameraClass;

	// ===== 编辑模式下“心控”功能输入 =====
	// 开始路径绘制
	void OnStartPathDrag();
	
	// 拖拽时更新路径预览
	void OnEditPathDragTriggered();
	
	// 拖拽结束，保留路径直到编辑模式关闭
	void OnEditPathDragCompleted();

	// 绘制路径
	void DrawPathPoints(const TArray<FVector>& Points, const FColor& Color) const;

	

	// 删除当前选中的ai路径
	void OnRemoveSelectedAIPath();

	// 计算路径长度
	float CalcPathLength(const TArray<FVector>& Points) const;

	// 按可用能量截断路径
	bool BuildClampedPathByEnergy(
		const TArray<FVector>& InPoints,
		float MaxAllowedLength, 
		TArray<FVector>& OutPoints, 
		FVector& OutTarget, 
		float& OutUsedLength) const;

	// 查找指定pawn的已锁定路径索引
	int32 FindLockedPathIndexByPawn(const APawn* InPawn) const;

	// 计算指定pawn已使用的能量
	float GetCommittedEnergyUsed(const APawn* IgnorePawn = nullptr) const;

	// =====能量回复机制=====

	// 刷新当前能量
	void RefreshCurrentPathEnergy();

	// 开始能量回复延时
	void StartEnergyRegenWithDelay();

	// 开始能量回复
	void BeginEnergyRegen();

	// 停止能量回复
	void StopEnergyRegen();

	// 每帧更新能量回复
	void TickEnergyRegen(float DeltaTime);

	// ===== ai单位信息显示功能 =====
	// 显示ai单位信息面板
	void ShowAIInfoPanel(AEnemyBase* InEnemy);

	// 隐藏ai单位信息面板
	void HideAIInfoPanel();

private:
	// 生成相机实例(运行时)
	UPROPERTY()
    AEditModeCamera* EditCamera = nullptr;

	// 缓存当前输入
	FVector2D EditPanInput = FVector2D::ZeroVector;

	// 旋转状态
	bool bEditRotateHeld = false;

};
