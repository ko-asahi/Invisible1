// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Trait/TraitDefinition.h"
#include "Enemy/Trait/TraitActionProfile.h"
#include "Enemy/Trait/TraitActionResolver.h"

// 写入并返回行为配置
FTraitResolvedAction UTraitActionResolver::ResolveAction(
    const FTraitInteractionRule& Rule,
    const UTraitActionProfile* ActionProfile)
{
    FTraitResolvedAction Out;

    // 当 InteractionActionTag 存在时，优先使用，如果为空，则使用 SuggestedBehaviorTag
    const FGameplayTag ActionTag = Rule.InteractionActionTag.IsValid() ? Rule.InteractionActionTag : Rule.SuggestedBehaviorTag;

    if(!ActionTag.IsValid())
    {
        return Out;
    }

    Out.ActionTag = ActionTag;

    // 先获取默认值并写入
    FTraitActionProfileEntry DefaultEntry;
    const bool bHasDefault = ActionProfile && ActionProfile->FindActionProfile(ActionTag, DefaultEntry);

    if(bHasDefault)
    {
        Out.ButtonText = DefaultEntry.DefaultButtonText;
        Out.EnergyCost = DefaultEntry.DefaultEnergyCost;
        Out.ExecutionRadius = DefaultEntry.DefaultExecutionRadius;
        Out.Duration = DefaultEntry.DefaultDuration;
    }


    // 检查规则配置是否合规，如果合规，则写入
    if(!Rule.InteractionActionButtonText.IsEmpty())
    {
        Out.ButtonText = Rule.InteractionActionButtonText;
    }
    if(Rule.ActionEnergyCostOverride >= 0.0f)
    {
        Out.EnergyCost = Rule.ActionEnergyCostOverride;
    }
    if(Rule.ExecutionRadiusOverride >= 0.0f)
    {
        Out.ExecutionRadius = Rule.ExecutionRadiusOverride;
    }
    if(Rule.DurationOverride >= 0.0f)
    {
        Out.Duration = Rule.DurationOverride;
    }

    Out.bValid = true;
    return Out;
}

