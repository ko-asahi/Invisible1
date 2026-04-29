// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/PatrolPath.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "Enemy/Trait/TraitSubsystem.h"
#include "Engine/GameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/WidgetComponent.h>
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/UI/AIInteractionButtonsWidget.h"
#include "Enemy/UI/AIDialogueBubbleWidget.h"
#include "MotionWarpingComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIEnemyInteractionDebug, Log, All);


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
	AlertBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 屏幕空间
	AlertBarWidgetComp->SetDrawSize(FVector2D(120.f, 16.f));
	AlertBarWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 220.f));

	AlertBarWidgetComp->SetDrawAtDesiredSize(true);      // 跟随Widget实际尺寸
	AlertBarWidgetComp->SetPivot(FVector2D(0.5f, 1.0f)); // 底边中心对齐到头顶点
	AlertBarWidgetComp->SetVisibility(false);             // 默认隐藏，警戒>0再显示

    // 按键组件
    InteractionButtonsWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionButtonsWidgetComp"));
    InteractionButtonsWidgetComp->SetupAttachment(GetCapsuleComponent());
    InteractionButtonsWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    InteractionButtonsWidgetComp->SetDrawAtDesiredSize(false);
    InteractionButtonsWidgetComp->SetDrawSize(FVector2D(500.f, 120.f));
    InteractionButtonsWidgetComp->SetPivot(FVector2D(0.5f, 0.0f));
    InteractionButtonsWidgetComp->SetRelativeRotation(FRotator::ZeroRotator);
    InteractionButtonsWidgetComp->SetRelativeScale3D(FVector::OneVector);
    InteractionButtonsWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
    InteractionButtonsWidgetComp->SetVisibility(false);

    // 对话框组件
    DialogueBubbleWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogueBubbleWidgetComp"));
    DialogueBubbleWidgetComp->SetupAttachment(GetCapsuleComponent());
    DialogueBubbleWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    DialogueBubbleWidgetComp->SetDrawAtDesiredSize(true);
    DialogueBubbleWidgetComp->SetPivot(FVector2D(0.5f, 1.0f));
    DialogueBubbleWidgetComp->SetRelativeRotation(FRotator::ZeroRotator);
    DialogueBubbleWidgetComp->SetRelativeScale3D(FVector::OneVector);
    DialogueBubbleWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 185.f)); // 比交互按钮略高
    DialogueBubbleWidgetComp->SetVisibility(false);

    // 运动扭曲组件
    MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

    // 初始化头顶按键
    if(InteractionButtonsWidgetClass && InteractionButtonsWidgetComp)
    {
        InteractionButtonsWidgetComp->SetWidgetClass(InteractionButtonsWidgetClass);
        InteractionButtonsWidgetComp->InitWidget();
    }
	
    // 初始化头顶对话框
    if(DialogueBubbleWidgetClass && DialogueBubbleWidgetComp)
    {
        DialogueBubbleWidgetComp->SetWidgetClass(DialogueBubbleWidgetClass);
        DialogueBubbleWidgetComp->InitWidget();
        DialogueBubbleWidgetComp->SetVisibility(false, true);
    }
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

// 设置状态标签 
void AEnemyBase::SetAIStateTag(FGameplayTag NewTag)
{
    if (!NewTag.IsValid()) return;
    if (AIStateTags.HasTagExact(NewTag)) return;

    AIStateTags.Reset();
    AIStateTags.AddTag(NewTag);

    UE_LOG(LogTemp, Log, TEXT("[AI] StateTag -> %s"), *AIStateTags.ToStringSimple());
}

void AEnemyBase::GetTraitDisplayEntries(UObject* WorldContextObject, TArray<FTraitDisplayEntry>& OutEntries) const
{
    OutEntries.Reset();

    const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : GetWorld();
    if (!World)
    {
        return;
    }

    UGameInstance* GI = World->GetGameInstance();
    UTraitSubsystem* TraitSub = GI ? GI->GetSubsystem<UTraitSubsystem>() : nullptr;
    if (!TraitSub)
    {
        return;
    }

    TArray<UTraitDefinition*> TraitDefs;
    TraitSub->ResolveTraitDefs(TraitTags, TraitDefs);

    for (const UTraitDefinition* Def : TraitDefs)
    {
        if (!Def)
        {
            continue;
        }

        bool bHasAIWithAI = false;
        bool bHasAIWithObject = false;

        for (const FTraitInteractionRule& Rule : Def->Rules)
        {
            if (Rule.InteractionType == ETraitInteractionType::AI_With_AI)
            {
                bHasAIWithAI = true;
            }
            else if (Rule.InteractionType == ETraitInteractionType::AI_With_Object)
            {
                bHasAIWithObject = true;
            }
        }

        ETraitDisplayCategory Category = ETraitDisplayCategory::Unknown;
        if (bHasAIWithAI)
        {
            Category = ETraitDisplayCategory::AIWithAI;
        }
        else if (bHasAIWithObject)
        {
            Category = ETraitDisplayCategory::AIWithObject;
        }

        FTraitDisplayEntry Entry;
        Entry.TraitTag = Def->TraitTag;
        Entry.DisplayName = Def->DisplayName.IsEmpty() ? FText::FromName(Def->TraitTag.GetTagName()) : Def->DisplayName;
        Entry.Category = Category;
        OutEntries.Add(MoveTemp(Entry));
    }
}

FText AEnemyBase::BuildTraitDisplayText(UObject* WorldContextObject, bool bUseRichTextMarkup) const
{
    TArray<FTraitDisplayEntry> Entries;
    GetTraitDisplayEntries(WorldContextObject, Entries);

    if (Entries.IsEmpty())
    {
        return FText::GetEmpty();
    }

    const FString Separator = TraitPanelFormatSettings.Separator.IsEmpty() ? TEXT(" | ") : TraitPanelFormatSettings.Separator;
    FString Result;
    Result.Reserve(Entries.Num() * 12);

    auto AppendWithStyle = [&](const FName& StyleTag, const FString& RawText)
    {
        if (bUseRichTextMarkup && !StyleTag.IsNone())
        {
            Result += FString::Printf(TEXT("<%s>%s</>"), *StyleTag.ToString(), *RawText);
        }
        else
        {
            Result += RawText;
        }
    };

    for (int32 Index = 0; Index < Entries.Num(); ++Index)
    {
        if (Index > 0)
        {
            Result += Separator;
        }

        const FString NameString = Entries[Index].DisplayName.ToString();
        switch (Entries[Index].Category)
        {
        case ETraitDisplayCategory::AIWithAI:
            AppendWithStyle(TraitPanelFormatSettings.AIWithAIStyleTag, NameString);
            break;
        case ETraitDisplayCategory::AIWithObject:
            AppendWithStyle(TraitPanelFormatSettings.AIWithObjectStyleTag, NameString);
            break;
        default:
            AppendWithStyle(TraitPanelFormatSettings.UnknownStyleTag, NameString);
            break;
        }
    }

    return FText::FromString(Result);
}

FAIInfoData AEnemyBase::BuildAIInfoDataForPanel(UObject* WorldContextObject, bool bUseRichTextMarkup) const
{
    FAIInfoData OutData = AIInfoData;
    OutData.EnemyTrait = BuildTraitDisplayText(WorldContextObject, bUseRichTextMarkup);
    return OutData;
}


// ===== ai交互UI相关 =====

// 显示头顶交互按钮
void AEnemyBase::ShowInteractionButtons(const TArray<FInteractionActionOption>& InActions, AEnemyBase* InSourceAI)
{
    if(!InteractionButtonsWidgetComp) return;
    
    if (InteractionButtonsWidgetClass && !InteractionButtonsWidgetComp->GetWidgetClass())
    {
        InteractionButtonsWidgetComp->SetWidgetClass(InteractionButtonsWidgetClass);
        InteractionButtonsWidgetComp->InitWidget();
    }

    UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(InteractionButtonsWidgetComp->GetUserWidgetObject());
    if (!Widget) 
    {
        UE_LOG(LogTemp, Warning, TEXT("显示头顶交互按钮失败: %s"), *GetNameSafe(InSourceAI));
        return;
    }

    // 绑定按键点击事件
    if (!Widget->OnActionClicked.IsAlreadyBound(this, &AEnemyBase::HandleInteractionButtonClicked))
    {
        Widget->OnActionClicked.AddDynamic(this, &AEnemyBase::HandleInteractionButtonClicked);
    }

    Widget->SetupAction(InActions, InSourceAI, this);
    InteractionButtonsWidgetComp->SetVisibility(InActions.Num() > 0,true);

    UE_LOG(LogTemp, Log, TEXT("显示头顶交互按钮: %s"), *GetNameSafe(InSourceAI));
    UE_LOG(LogAIEnemyInteractionDebug, Log, TEXT("[显示头顶交互按钮] Enter Self=%s Source=%s InActions=%d Comp=%s WidgetClass=%s"),
    *GetNameSafe(this),
    *GetNameSafe(InSourceAI),
    InActions.Num(),
    *GetNameSafe(InteractionButtonsWidgetComp),
    *GetNameSafe(InteractionButtonsWidgetClass));
}

// 隐藏头顶交互按钮
void AEnemyBase::HideInteractionButtons()
{
    if(!InteractionButtonsWidgetComp) return;

    if(UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(InteractionButtonsWidgetComp->GetUserWidgetObject()))
    {
        Widget->ClearActions();
    }

    InteractionButtonsWidgetComp->SetVisibility(false,true);
}

// 按键点击句柄
void AEnemyBase::HandleInteractionButtonClicked(
    FInteractionActionOption ActionData,
    AEnemyBase* SourceAI,
    AActor* TargetActor)
{
    OnInteractionActionChosen.Broadcast(ActionData, SourceAI, TargetActor);
}


// ===== ai对话框相关 =====

// 显示头顶对话框
void AEnemyBase::ShowDialogueBubble(const FText& InText)
{
    if(!DialogueBubbleWidgetComp) return;

    if(InText.IsEmpty())
    {
        HideDialogueBubble();
        return;
    }

    if(DialogueBubbleWidgetClass && !DialogueBubbleWidgetComp->GetWidgetClass())
    {
        DialogueBubbleWidgetComp->SetWidgetClass(DialogueBubbleWidgetClass);
        DialogueBubbleWidgetComp->InitWidget();
    }

    UAIDialogueBubbleWidget* Widget = Cast<UAIDialogueBubbleWidget>(DialogueBubbleWidgetComp->GetUserWidgetObject());
    if(!Widget)
    {
        UE_LOG(LogTemp, Warning, TEXT("显示头顶对话框失败: %s"), *GetNameSafe(this));
        return;
    }

    Widget->ShowDialogueText(InText);
    DialogueBubbleWidgetComp->SetVisibility(true, true);
}

// 隐藏头顶对话框
void AEnemyBase::HideDialogueBubble()
{
    if(!DialogueBubbleWidgetComp) return;

    if(UAIDialogueBubbleWidget* Widget = Cast<UAIDialogueBubbleWidget>(DialogueBubbleWidgetComp->GetUserWidgetObject()))
    {
        Widget->ClearDialogueText();
    }

    DialogueBubbleWidgetComp->SetVisibility(false, true);
}
