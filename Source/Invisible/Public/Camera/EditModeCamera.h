// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SceneComponent.h>
#include "Components/DecalComponent.h"      
#include "Materials/MaterialInterface.h"  
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EditModeCamera.generated.h"

/**
 * 编辑模式相机
 */

UCLASS()
class INVISIBLE_API AEditModeCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEditModeCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// 根组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	// 相机旋转圆心
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CameraPivot;

	// 弹簧臂
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraBoom;


	// 相机组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	// 鼠标投影指示器组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* GroundRingDecal;

	// 指示器贴花材质（指示器的贴花效果）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicator")
	UMaterialInterface* GroundRingDecalMaterial = nullptr;

	// Decal尺寸：X=投射厚度，Y/Z=范围
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indicator")
	FVector GroundRingDecalSize = FVector(32.0f, 96.0f, 96.0f);

	// 生成时相机俯视角
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraPitch = -45.0f;

	// 相机平移速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraPanSpeed = 1500.0f;

	// 相机旋转速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraOrbitSpeed = 0.3f;


	// 初始化朝向（仅初始化Yaw，不改变位置）
	void InitializeCamera(float InitialYaw);

	// 每帧更新相机位置
	// 相机平移
	void PanCamera(const FVector2D& InputAxis, float DeltaTime);

	// 相机旋转
	void OrbitCamera(float DeltaYaw);

	// 更新鼠标投影指示器
	void UpdateGroundRing(APlayerController* PC);


private:	
	// 相机在世界空间中的偏航角
	float CurrentYaw = 0.0f;

	// 应用旋转
	void ApplyRotation();

};
