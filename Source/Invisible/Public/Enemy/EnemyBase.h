// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy/PatrolPath.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Enemy/Interaction/AIInteractionTypes.h"
#include "EnemyBase.generated.h"

/**
 * EnemyBase 是敌人的基类，包含了敌人的基本属性和行为
 */

class UAIInteractionButtonsWidget;

// 敌人警戒配置结构体
USTRUCT(BlueprintType)
struct FEnemyAlertConfig
{
    GENERATED_BODY()

    // =====视觉警戒值检测相关=====

    // 最大警戒值
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float MaxAlertness = 100.0f;

    // 三段视觉警戒距离

    // 近距警戒
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float NearRange = 300.f;

    // 中距警戒
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float MidRange = 700.f;

    // 远距警戒
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float FarRange = 1200.f;

    // 三段警戒值增长速率

    // 近距警戒值增长速率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float NearGainRate = 45.0f;

    // 中距警戒值增长速率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float MidGainRate = 25.0f;

    // 远距警戒值增长速率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float FarGainRate = 10.0f;

    // 视野外警戒值衰减速率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float AlertDecayRate = 20.0f;

    // 玩家站立时视觉警戒值增长倍率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float StandGainMultiplier = 1.0f;

    // 玩家行走时视觉警戒值增长倍率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float WalkGainMultiplier = 1.0f;

    // 玩家奔跑时视觉警戒值增长倍率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float RunGainMultiplier = 1.5f;

    // 玩家蹲下时视觉警戒值增长倍率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float CrouchIdleGainMultiplier = 0.3f;

    // 玩家蹲走时视觉警戒值增长倍率
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float CrouchWalkGainMultiplier = 0.6f;

    // 状态阈值

    // 怀疑阈值
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float SuspiciousThreshold = 50.f;

    // 打探阈值
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float ChaseThreshold = 80.f;

    // 目标丢失阈值
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float LoseTargetThreshold = 15.f;

    // 打探阶段看向目标点时间
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float InvestigateLookDuration = 2.0f;

    // 每次听到声音增加的警戒值
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert", meta=(ClampMin="0.0"))
    float HearingAlertGain = 10.0f;
};

// ai敌人信息
USTRUCT(BlueprintType)
struct FAIInfoData
{
    GENERATED_BODY()

    // 敌人头像
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    UTexture2D* EnemyAvatar = nullptr;

    // 敌人状态
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    FText EnemyStatus;

    // 敌人职级
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    FText EnemyRank;

    // 敌人特质
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    FText EnemyTrait;

    // 敌人习惯
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    FText EnemyHabit;
};

// UI中的特质分类，用于区分不同颜色
UENUM(BlueprintType)
enum class ETraitDisplayCategory : uint8
{
    AIWithAI        UMETA(DisplayName="AI与AI互动"),
    AIWithObject    UMETA(DisplayName="AI与物体互动"),
    Unknown         UMETA(DisplayName="未分类")
};

// 单个特质在UI中的显示数据
USTRUCT(BlueprintType)
struct FTraitDisplayEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category="AI|Trait|UI")
    FGameplayTag TraitTag;

    UPROPERTY(BlueprintReadOnly, Category="AI|Trait|UI")
    FText DisplayName;

    UPROPERTY(BlueprintReadOnly, Category="AI|Trait|UI")
    ETraitDisplayCategory Category = ETraitDisplayCategory::Unknown;
};

// 特质文本拼接配置（默认用于 RichTextBlock）
USTRUCT(BlueprintType)
struct FTraitPanelFormatSettings
{
    GENERATED_BODY()

    // 特质之间的分隔符
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Trait|UI")
    FString Separator = TEXT(" | ");

    // AI与AI互动特质在 RichText 中使用的样式标签名
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Trait|UI")
    FName AIWithAIStyleTag = TEXT("Trait.AIWithAI");

    // AI与物体互动特质在 RichText 中使用的样式标签名
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Trait|UI")
    FName AIWithObjectStyleTag = TEXT("Trait.AIWithObject");

    // 未分类特质在 RichText 中使用的样式标签名（可留空）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Trait|UI")
    FName UnknownStyleTag = NAME_None;
};


UCLASS()
class INVISIBLE_API AEnemyBase : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // =====警戒值可视化=====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
    class UWidgetComponent* AlertBarWidgetComp;

	// ===== AI相关 =====
	// 分配给该敌人的巡逻路径（由多个巡逻点组成）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	APatrolPath* AssignedPatrolPath = nullptr;

	// 当前目标巡逻点索引
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    int32 CurrentPatrolPointIndex = 0;

	// 巡逻速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float PatrolSpeed = 300.0f;

	// 视野半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
	float SightRadius = 1200.0f;

	// 视野感知角度（总视角的一半）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
	float HalfViewAngle = 60.f;

	// 敌人警戒配置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Alert")
	FEnemyAlertConfig AlertConfig;


	// 获取下一个巡逻点
	AActor* GetNextPatrolPoint();

    // 敌人信息（使每个实例都能独立填写）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Info")
    FAIInfoData AIInfoData;


    // 敌人状态机标签
    // 获取标签
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
    {
        TagContainer.AppendTags(AIStateTags);
    }

    // 设置状态标签
    UFUNCTION(BlueprintCallable, Category="AI|State")
    void SetAIStateTag(FGameplayTag NewTag);

    // 判断是否拥有标签
    UFUNCTION(BlueprintPure, Category="AI|State")
    bool HasAIStateTag(FGameplayTag QueryTag) const
    {
        return AIStateTags.HasTagExact(QueryTag);
    }

    // 标签容器，用于存储 AI 的运动行为
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI|State")
    FGameplayTagContainer AIStateTags;

    // 特质 Tag 容器，用于存储敌人所包含的特质 Tag，用于特质交互
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Trait", meta=(Categories="Trait.AI"))
    FGameplayTagContainer TraitTags;

	// 行为树
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

    // 特质面板拼接配置（主要用于敌方信息面板）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Trait|UI")
    FTraitPanelFormatSettings TraitPanelFormatSettings;

    // 获取当前敌人的特质显示条目（已按优先级排序）
    UFUNCTION(BlueprintPure, Category="AI|Trait|UI")
    void GetTraitDisplayEntries(UObject* WorldContextObject, TArray<FTraitDisplayEntry>& OutEntries) const;

    // 构建特质文本；bUseRichTextMarkup=true 时返回带样式标签的文本
    UFUNCTION(BlueprintPure, Category="AI|Trait|UI")
    FText BuildTraitDisplayText(UObject* WorldContextObject, bool bUseRichTextMarkup = true) const;

    // 生成用于敌方信息面板的 AIInfoData（会覆盖 EnemyTrait）
    UFUNCTION(BlueprintCallable, Category="AI|Info")
    FAIInfoData BuildAIInfoDataForPanel(UObject* WorldContextObject, bool bUseRichTextMarkup = true) const;

    // ===== ai交互UI相关 =====

    // 头顶交互按钮组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI|Interaction")
    class UWidgetComponent* InteractionButtonsWidgetComp;

    // 头顶交互按钮类（蓝图指定）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI|Interaction")
    TSubclassOf<UAIInteractionButtonsWidget> InteractionButtonsWidgetClass;

    // 单击按钮事件
    UPROPERTY(BlueprintAssignable, Category="AI|Interaction")
    FOnAIInteractionActionClicked OnInteractionActionChosen;

    // 显示头顶交互按钮
    UFUNCTION(BlueprintCallable, Category="AI|Interaction")
    void ShowInteractionButtons(const TArray<FInteractionActionOption>& InActions, AEnemyBase* InSourceAI);

    // 隐藏头顶交互按钮
    UFUNCTION(BlueprintCallable, Category="AI|Interaction")
    void HideInteractionButtons();

    // ===== ai交互行为相关 =====

    // 互动时转向速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction", meta = (ClampMin = "0.0"))
    float InteractionTurnSpeed = 180.0f;


protected:
    // 按键点击句柄
    UFUNCTION()
    void HandleInteractionButtonClicked(
        FInteractionActionOption ActionData,
        AEnemyBase* SourceAI,
        AActor* TargetActor);
};
