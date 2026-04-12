// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Trait/TraitInteractionResolver.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/Trait/TraitSubsystem.h"
#include "Enemy/Interface/TraitTargetInterface.h"


FTraitInteractionDecision UTraitInteractionResolver::EvaluateInteraction(
    UObject* WorldContextObject,
    AEnemyBase* SourceAI,
    AActor* TargetActor,
    ETraitInteractionType InteractionType)
{
    FTraitInteractionDecision Out;
    if(!WorldContextObject || !SourceAI || !TargetActor) return Out;

    UWorld* World = WorldContextObject->GetWorld();
    if(!World) return Out;


    // 获取本局游戏中的特质子系统
    UGameInstance* GI = World->GetGameInstance();
    UTraitSubsystem* TraitSub = GI ? GI->GetSubsystem<UTraitSubsystem>() : nullptr;
    if(!TraitSub) return Out;

    // 通过接口获取 Target 的标签
    FGameplayTagContainer TargetTags;
    if(TargetActor->GetClass()->ImplementsInterface(UTraitTargetInterface::StaticClass()))
    {
        TargetTags = ITraitTargetInterface::Execute_GetInteractionTargetTags(TargetActor);
    }

    // 解析 SourceAI 的标签，获取对应的特质定义
    TArray<UTraitDefinition*> TraitDefs;
    TraitSub->ResolveTraitDefs(SourceAI->TraitTags, TraitDefs);

    // 遍历每个特质定义，计算互动权重
    // float Score = 0.0f;
    bool bMatchedAnyRule = false;
    FGameplayTag BestBehaviorTag;
    int32 BestPriority = TNumericLimits<int32>::Min();

    for(UTraitDefinition* Def : TraitDefs)
    {
        if(!Def) continue;

        for(const FTraitInteractionRule& Rule : Def->Rules)
        {
            if(Rule.InteractionType != InteractionType) continue;

            const bool bPassTargetFilter = Rule.TargetTagsAny.IsEmpty() || TargetTags.HasAny(Rule.TargetTagsAny);
            if(!bPassTargetFilter) continue;

            //Score += Rule.ScoreDelta;
            bMatchedAnyRule = true;
            Out.MatchedTraitDescriptions.Add(Def->DisplayName);

            if(Def->Priority > BestPriority && Rule.SuggestedBehaviorTag.IsValid())
            {
                BestPriority = Def->Priority;
                BestBehaviorTag = Rule.SuggestedBehaviorTag;
            }
        }
    }

    //Out.FinalScore = Score;
    Out.SuggestedBehaviorTag = BestBehaviorTag;

    Out.bCanExecute = bMatchedAnyRule;
    return Out;
}
