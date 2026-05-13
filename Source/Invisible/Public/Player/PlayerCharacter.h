// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SceneComponent.h>
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PlayerCharacter.generated.h"

class ASIZZ_DecalBaseActor;
class USIZZ_IndicatorBehaviourDefinition;

// 噪声圈配置结构体
USTRUCT()
struct FNoiseProfile
{
    GENERATED_BODY()
    bool bShowRing = false; // 是否显示噪声圈
    bool bEmitNoise = false; // 是否产生噪音
    float Loudness = 0.f;   // 0~1，响度
    float Interval = 0.5f;  // 脚步间隔（秒）
};


UCLASS()
class INVISIBLE_API APlayerCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// ===== 相机相关 =====
	// 弹簧臂旋转圆心
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* CameraPivot;

	// 相机旋转半径（弹簧臂）
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraBoom;

	// 玩家跟随摄像机
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

	// 相机在世界空间中的偏航角
	float CameraWorldYaw = 0.0f;

	// 单独旋转相机
	void OrbitCamera(float DeltaYaw);

	// 获取相机在水平面上的偏航角
	float GetCameraYaw() const;

	// ===== 移动相关 =====
public:
	// 蹲下移动速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchWalkSpeed = 300.0f;


	// 正常移动速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float NormalWalkSpeed = 600.0f;

	// 奔跑速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float RunSpeed = 1000.0f;

	// 是否处于奔跑状态
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsRunning = false;

	// ===== 游戏移动标签相关 =====
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.AppendTags(MovementStateTags);
	}

	// 当前移动状态（单Tag）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	FGameplayTagContainer MovementStateTags;

	// 移动速度判断阈值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MinMovementSpeed = 10.0f;


	// ===== 听觉相关 =====

	// 行走脚步响度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float WalkFootstepLoudness = 0.5f;

	// 行走脚步频率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float WalkFootstepFrequency = 0.5f;

	// 奔跑脚步响度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float RunFootstepLoudness = 1.0f;

	// 奔跑脚步频率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float RunFootstepFrequency = 0.3f;

	// 蹲下行走脚步响度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float CrouchFootstepLoudness = 0.1f;

	// 蹲下行走脚步频率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Footstep",
			meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float CrouchFootstepFrequency = 0.8f;


	// 绘制听觉范围
    void DrawHearingRange(float Loudness, float Duration);

	// 噪声圈效果实现

	// 噪声圈贴花组件  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Noise|Visual")
	UDecalComponent* NoiseRingDecal;

	// 噪声圈基础材质
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Noise|Visual")
	UMaterialInterface* NoiseRingMaterialBase;

	// 噪声圈动态材质
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* NoiseRingMID;

	// 噪声圈持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual")
	float NoiseRingDuration = 0.20f;

	// 噪声圈投射深度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual")
	float NoiseRingProjectionDepth = 200.0f;

	// 关卡最小坐标（遮罩层）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Mask")
	FVector2D PlayAreaMinWS = FVector2D(-5000.f, -5000.f);

	// 关卡最大坐标（遮罩层）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Mask")
	FVector2D PlayAreaSizeWS = FVector2D(10000.f, 10000.f);

	// 运行时
	// 噪声圈剩余时间
	float NoiseRingTimeLeft = 0.f;
	// 噪声圈总时间
	float NoiseRingTotalTime = 0.f;
		
	// 噪声圈半径
	float CurrentRingRadius = 0.f;
	// 噪声圈透明度
	float CurrentRingOpacity = 0.f;

	// 显示噪声圈
	void ShowNoiseRing(float EffectiveRadius, float Duration);

	// 更新噪声圈
	void UpdateNoiseRingVisual(float DeltaTime);

	// 是否启用 SIZZ 声音圈可视化（脚步事件触发）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual|SIZZ")
	bool bEnableSizzNoiseIndicator = true;

	// SIZZ 圆形指示器定义（建议使用插件 BPDA_SI_DEF_Circle* 样例）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual|SIZZ")
	USIZZ_IndicatorBehaviourDefinition* NoiseCircleIndicatorDefinition = nullptr;

	// SIZZ 声音圈显示时长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual|SIZZ", meta=(ClampMin="0.05"))
	float NoiseCircleIndicatorDuration = 0.25f;

	// 半径修正系数（插件圆形投射与实际听觉半径可能有比例差）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise|Visual|SIZZ", meta=(ClampMin="0.1"))
	float NoiseCircleRadiusScale = 2.0f;

	// 通过Tag获取噪声圈参数
	bool ResolveNoiseProfileByTag(FNoiseProfile& OutProfile) const;


protected:
	// 事件驱动更新Tag
    virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
    virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
    virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	
	// 监听全局听觉范围变化
	UFUNCTION()
	void HandleGlobalHearingRangeChanged(float NewRange);


private:
	// 显式注册为听觉刺激源，避免不同版本下噪声事件无法被感知系统关联
	UPROPERTY(VisibleAnywhere, Category="AI|Perception")
	UAIPerceptionStimuliSourceComponent* HearingStimuliSourceComp = nullptr;

	// 缓存Tag
	FGameplayTag Tag_Idle;
	FGameplayTag Tag_Walk;
	FGameplayTag Tag_CrouchIdle;
	FGameplayTag Tag_CrouchWalk;
	FGameplayTag Tag_Run;

	// 更新角色Tag
	void UpdateMovementStateTags();

	// 上报脚步噪音（按移动状态控制响度/频率）
	void ReportFootstepNoise(float DeltaTime);

	// 脚步计时器
	float FootstepTimer = 0.0f;

	// 运行时缓存的全局听觉范围（由 GameState 广播驱动）
	float CachedGlobalHearingRange = 0.0f;

	UPROPERTY(Transient)
	TObjectPtr<ASIZZ_DecalBaseActor> ActiveNoiseCircleIndicator = nullptr;

	void SpawnSizzNoiseIndicator(float EffectiveRadius, float Duration);
	void UpdateSizzNoiseIndicatorFollow() const;


};
