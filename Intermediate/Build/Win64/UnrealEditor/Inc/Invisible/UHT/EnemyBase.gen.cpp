// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/EnemyBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEnemyBase() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBehaviorTree_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyBase();
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_APatrolPath_NoRegister();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FAIInfoData();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FEnemyAlertConfig();
UMG_API UClass* Z_Construct_UClass_UWidgetComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FEnemyAlertConfig *************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEnemyAlertConfig;
class UScriptStruct* FEnemyAlertConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEnemyAlertConfig, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("EnemyAlertConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * EnemyBase \xe6\x98\xaf\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\x9f\xba\xe7\xb1\xbb\xef\xbc\x8c\xe5\x8c\x85\xe5\x90\xab\xe4\xba\x86\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\x9f\xba\xe6\x9c\xac\xe5\xb1\x9e\xe6\x80\xa7\xe5\x92\x8c\xe8\xa1\x8c\xe4\xb8\xba\n */// \xe6\x95\x8c\xe4\xba\xba\xe8\xad\xa6\xe6\x88\x92\xe9\x85\x8d\xe7\xbd\xae\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "EnemyBase \xe6\x98\xaf\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\x9f\xba\xe7\xb1\xbb\xef\xbc\x8c\xe5\x8c\x85\xe5\x90\xab\xe4\xba\x86\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\x9f\xba\xe6\x9c\xac\xe5\xb1\x9e\xe6\x80\xa7\xe5\x92\x8c\xe8\xa1\x8c\xe4\xb8\xba\n // \xe6\x95\x8c\xe4\xba\xba\xe8\xad\xa6\xe6\x88\x92\xe9\x85\x8d\xe7\xbd\xae\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxAlertness_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x9c\x80\xe5\xa4\xa7\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\x80\xe5\xa4\xa7\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NearRange_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbf\x91\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x91\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidRange_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xb8\xad\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xb8\xad\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarRange_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbf\x9c\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x9c\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NearGainRate_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbf\x91\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x91\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidGainRate_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xb8\xad\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xb8\xad\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FarGainRate_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbf\x9c\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x9c\xe8\xb7\x9d\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\xa2\x9e\xe9\x95\xbf\xe9\x80\x9f\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlertDecayRate_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x86\xe9\x87\x8e\xe5\xa4\x96\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe8\xa1\xb0\xe5\x87\x8f\xe9\x80\x9f\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe9\x87\x8e\xe5\xa4\x96\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe8\xa1\xb0\xe5\x87\x8f\xe9\x80\x9f\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuspiciousThreshold_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x80\x80\xe7\x96\x91\xe9\x98\x88\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x80\x80\xe7\x96\x91\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChaseThreshold_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x89\x93\xe6\x8e\xa2\xe9\x98\x88\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x89\x93\xe6\x8e\xa2\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoseTargetThreshold_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xae\xe6\xa0\x87\xe4\xb8\xa2\xe5\xa4\xb1\xe9\x98\x88\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xae\xe6\xa0\x87\xe4\xb8\xa2\xe5\xa4\xb1\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InvestigateLookDuration_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x89\x93\xe6\x8e\xa2\xe9\x98\xb6\xe6\xae\xb5\xe7\x9c\x8b\xe5\x90\x91\xe7\x9b\xae\xe6\xa0\x87\xe7\x82\xb9\xe6\x97\xb6\xe9\x97\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x89\x93\xe6\x8e\xa2\xe9\x98\xb6\xe6\xae\xb5\xe7\x9c\x8b\xe5\x90\x91\xe7\x9b\xae\xe6\xa0\x87\xe7\x82\xb9\xe6\x97\xb6\xe9\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingAlertGain_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\xaf\x8f\xe6\xac\xa1\xe5\x90\xac\xe5\x88\xb0\xe5\xa3\xb0\xe9\x9f\xb3\xe5\xa2\x9e\xe5\x8a\xa0\xe7\x9a\x84\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe6\xac\xa1\xe5\x90\xac\xe5\x88\xb0\xe5\xa3\xb0\xe9\x9f\xb3\xe5\xa2\x9e\xe5\x8a\xa0\xe7\x9a\x84\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxAlertness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NearRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MidRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FarRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NearGainRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MidGainRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FarGainRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AlertDecayRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SuspiciousThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChaseThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LoseTargetThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InvestigateLookDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HearingAlertGain;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEnemyAlertConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MaxAlertness = { "MaxAlertness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, MaxAlertness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxAlertness_MetaData), NewProp_MaxAlertness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_NearRange = { "NearRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, NearRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NearRange_MetaData), NewProp_NearRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MidRange = { "MidRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, MidRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidRange_MetaData), NewProp_MidRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_FarRange = { "FarRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, FarRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarRange_MetaData), NewProp_FarRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_NearGainRate = { "NearGainRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, NearGainRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NearGainRate_MetaData), NewProp_NearGainRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MidGainRate = { "MidGainRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, MidGainRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidGainRate_MetaData), NewProp_MidGainRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_FarGainRate = { "FarGainRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, FarGainRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FarGainRate_MetaData), NewProp_FarGainRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_AlertDecayRate = { "AlertDecayRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, AlertDecayRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlertDecayRate_MetaData), NewProp_AlertDecayRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_SuspiciousThreshold = { "SuspiciousThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, SuspiciousThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuspiciousThreshold_MetaData), NewProp_SuspiciousThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_ChaseThreshold = { "ChaseThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, ChaseThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChaseThreshold_MetaData), NewProp_ChaseThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_LoseTargetThreshold = { "LoseTargetThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, LoseTargetThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoseTargetThreshold_MetaData), NewProp_LoseTargetThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_InvestigateLookDuration = { "InvestigateLookDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, InvestigateLookDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InvestigateLookDuration_MetaData), NewProp_InvestigateLookDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_HearingAlertGain = { "HearingAlertGain", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAlertConfig, HearingAlertGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingAlertGain_MetaData), NewProp_HearingAlertGain_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MaxAlertness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_NearRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MidRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_FarRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_NearGainRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_MidGainRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_FarGainRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_AlertDecayRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_SuspiciousThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_ChaseThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_LoseTargetThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_InvestigateLookDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewProp_HearingAlertGain,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"EnemyAlertConfig",
	Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::PropPointers),
	sizeof(FEnemyAlertConfig),
	alignof(FEnemyAlertConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEnemyAlertConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.InnerSingleton, Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FEnemyAlertConfig.InnerSingleton;
}
// ********** End ScriptStruct FEnemyAlertConfig ***************************************************

// ********** Begin ScriptStruct FAIInfoData *******************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FAIInfoData;
class UScriptStruct* FAIInfoData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FAIInfoData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FAIInfoData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAIInfoData, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("AIInfoData"));
	}
	return Z_Registration_Info_UScriptStruct_FAIInfoData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FAIInfoData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ai\xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ai\xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyAvatar_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe5\xa4\xb4\xe5\x83\x8f\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe5\xa4\xb4\xe5\x83\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyStatus_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe7\x8a\xb6\xe6\x80\x81\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyRank_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe8\x81\x8c\xe7\xba\xa7\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe8\x81\x8c\xe7\xba\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyTrait_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe7\x89\xb9\xe8\xb4\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe7\x89\xb9\xe8\xb4\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyHabit_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe4\xb9\xa0\xe6\x83\xaf\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe4\xb9\xa0\xe6\x83\xaf" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EnemyAvatar;
	static const UECodeGen_Private::FTextPropertyParams NewProp_EnemyStatus;
	static const UECodeGen_Private::FTextPropertyParams NewProp_EnemyRank;
	static const UECodeGen_Private::FTextPropertyParams NewProp_EnemyTrait;
	static const UECodeGen_Private::FTextPropertyParams NewProp_EnemyHabit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAIInfoData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyAvatar = { "EnemyAvatar", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAIInfoData, EnemyAvatar), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyAvatar_MetaData), NewProp_EnemyAvatar_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyStatus = { "EnemyStatus", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAIInfoData, EnemyStatus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyStatus_MetaData), NewProp_EnemyStatus_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyRank = { "EnemyRank", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAIInfoData, EnemyRank), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyRank_MetaData), NewProp_EnemyRank_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyTrait = { "EnemyTrait", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAIInfoData, EnemyTrait), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyTrait_MetaData), NewProp_EnemyTrait_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyHabit = { "EnemyHabit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAIInfoData, EnemyHabit), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyHabit_MetaData), NewProp_EnemyHabit_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAIInfoData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyAvatar,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyStatus,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyRank,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyTrait,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAIInfoData_Statics::NewProp_EnemyHabit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAIInfoData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAIInfoData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"AIInfoData",
	Z_Construct_UScriptStruct_FAIInfoData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAIInfoData_Statics::PropPointers),
	sizeof(FAIInfoData),
	alignof(FAIInfoData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAIInfoData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAIInfoData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAIInfoData()
{
	if (!Z_Registration_Info_UScriptStruct_FAIInfoData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FAIInfoData.InnerSingleton, Z_Construct_UScriptStruct_FAIInfoData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FAIInfoData.InnerSingleton;
}
// ********** End ScriptStruct FAIInfoData *********************************************************

// ********** Begin Class AEnemyBase ***************************************************************
void AEnemyBase::StaticRegisterNativesAEnemyBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AEnemyBase;
UClass* AEnemyBase::GetPrivateStaticClass()
{
	using TClass = AEnemyBase;
	if (!Z_Registration_Info_UClass_AEnemyBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("EnemyBase"),
			Z_Registration_Info_UClass_AEnemyBase.InnerSingleton,
			StaticRegisterNativesAEnemyBase,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AEnemyBase.InnerSingleton;
}
UClass* Z_Construct_UClass_AEnemyBase_NoRegister()
{
	return AEnemyBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEnemyBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Enemy/EnemyBase.h" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlertBarWidgetComp_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// =====\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\x8f\xaf\xe8\xa7\x86\xe5\x8c\x96=====\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=====\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe5\x8f\xaf\xe8\xa7\x86\xe5\x8c\x96=====" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssignedPatrolPath_MetaData[] = {
		{ "Category", "Patrol" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ===== AI\xe7\x9b\xb8\xe5\x85\xb3 =====\n// \xe5\x88\x86\xe9\x85\x8d\xe7\xbb\x99\xe8\xaf\xa5\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\xb7\xa1\xe9\x80\xbb\xe8\xb7\xaf\xe5\xbe\x84\xef\xbc\x88\xe7\x94\xb1\xe5\xa4\x9a\xe4\xb8\xaa\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xbb\x84\xe6\x88\x90\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "===== AI\xe7\x9b\xb8\xe5\x85\xb3 =====\n\xe5\x88\x86\xe9\x85\x8d\xe7\xbb\x99\xe8\xaf\xa5\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84\xe5\xb7\xa1\xe9\x80\xbb\xe8\xb7\xaf\xe5\xbe\x84\xef\xbc\x88\xe7\x94\xb1\xe5\xa4\x9a\xe4\xb8\xaa\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xbb\x84\xe6\x88\x90\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPatrolPointIndex_MetaData[] = {
		{ "Category", "Patrol" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe7\x9b\xae\xe6\xa0\x87\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xb4\xa2\xe5\xbc\x95\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe7\x9b\xae\xe6\xa0\x87\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xb4\xa2\xe5\xbc\x95" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolSpeed_MetaData[] = {
		{ "Category", "Patrol" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe9\x80\xbb\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe9\x80\xbb\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SightRadius_MetaData[] = {
		{ "Category", "AI|Perception" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x86\xe9\x87\x8e\xe5\x8d\x8a\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe9\x87\x8e\xe5\x8d\x8a\xe5\xbe\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HalfViewAngle_MetaData[] = {
		{ "Category", "AI|Perception" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x86\xe9\x87\x8e\xe6\x84\x9f\xe7\x9f\xa5\xe8\xa7\x92\xe5\xba\xa6\xef\xbc\x88\xe6\x80\xbb\xe8\xa7\x86\xe8\xa7\x92\xe7\x9a\x84\xe4\xb8\x80\xe5\x8d\x8a\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe9\x87\x8e\xe6\x84\x9f\xe7\x9f\xa5\xe8\xa7\x92\xe5\xba\xa6\xef\xbc\x88\xe6\x80\xbb\xe8\xa7\x86\xe8\xa7\x92\xe7\x9a\x84\xe4\xb8\x80\xe5\x8d\x8a\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlertConfig_MetaData[] = {
		{ "Category", "AI|Perception|Alert" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe8\xad\xa6\xe6\x88\x92\xe9\x85\x8d\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe8\xad\xa6\xe6\x88\x92\xe9\x85\x8d\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIInfoData_MetaData[] = {
		{ "Category", "AI|Info" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf\xef\xbc\x88\xe4\xbd\xbf\xe6\xaf\x8f\xe4\xb8\xaa\xe5\xae\x9e\xe4\xbe\x8b\xe9\x83\xbd\xe8\x83\xbd\xe7\x8b\xac\xe7\xab\x8b\xe5\xa1\xab\xe5\x86\x99\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf\xef\xbc\x88\xe4\xbd\xbf\xe6\xaf\x8f\xe4\xb8\xaa\xe5\xae\x9e\xe4\xbe\x8b\xe9\x83\xbd\xe8\x83\xbd\xe7\x8b\xac\xe7\xab\x8b\xe5\xa1\xab\xe5\x86\x99\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BehaviorTree_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa1\x8c\xe4\xb8\xba\xe6\xa0\x91\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\x8c\xe4\xb8\xba\xe6\xa0\x91" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AlertBarWidgetComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AssignedPatrolPath;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentPatrolPointIndex;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SightRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HalfViewAngle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AlertConfig;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AIInfoData;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BehaviorTree;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_AlertBarWidgetComp = { "AlertBarWidgetComp", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, AlertBarWidgetComp), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlertBarWidgetComp_MetaData), NewProp_AlertBarWidgetComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_AssignedPatrolPath = { "AssignedPatrolPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, AssignedPatrolPath), Z_Construct_UClass_APatrolPath_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssignedPatrolPath_MetaData), NewProp_AssignedPatrolPath_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_CurrentPatrolPointIndex = { "CurrentPatrolPointIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, CurrentPatrolPointIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentPatrolPointIndex_MetaData), NewProp_CurrentPatrolPointIndex_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_PatrolSpeed = { "PatrolSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, PatrolSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolSpeed_MetaData), NewProp_PatrolSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_SightRadius = { "SightRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, SightRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SightRadius_MetaData), NewProp_SightRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_HalfViewAngle = { "HalfViewAngle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, HalfViewAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HalfViewAngle_MetaData), NewProp_HalfViewAngle_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_AlertConfig = { "AlertConfig", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, AlertConfig), Z_Construct_UScriptStruct_FEnemyAlertConfig, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlertConfig_MetaData), NewProp_AlertConfig_MetaData) }; // 1030398055
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_AIInfoData = { "AIInfoData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, AIInfoData), Z_Construct_UScriptStruct_FAIInfoData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIInfoData_MetaData), NewProp_AIInfoData_MetaData) }; // 461720737
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyBase_Statics::NewProp_BehaviorTree = { "BehaviorTree", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBase, BehaviorTree), Z_Construct_UClass_UBehaviorTree_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BehaviorTree_MetaData), NewProp_BehaviorTree_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_AlertBarWidgetComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_AssignedPatrolPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_CurrentPatrolPointIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_PatrolSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_SightRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_HalfViewAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_AlertConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_AIInfoData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBase_Statics::NewProp_BehaviorTree,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AEnemyBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyBase_Statics::ClassParams = {
	&AEnemyBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AEnemyBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyBase()
{
	if (!Z_Registration_Info_UClass_AEnemyBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyBase.OuterSingleton, Z_Construct_UClass_AEnemyBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyBase);
AEnemyBase::~AEnemyBase() {}
// ********** End Class AEnemyBase *****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEnemyAlertConfig::StaticStruct, Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics::NewStructOps, TEXT("EnemyAlertConfig"), &Z_Registration_Info_UScriptStruct_FEnemyAlertConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEnemyAlertConfig), 1030398055U) },
		{ FAIInfoData::StaticStruct, Z_Construct_UScriptStruct_FAIInfoData_Statics::NewStructOps, TEXT("AIInfoData"), &Z_Registration_Info_UScriptStruct_FAIInfoData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAIInfoData), 461720737U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyBase, AEnemyBase::StaticClass, TEXT("AEnemyBase"), &Z_Registration_Info_UClass_AEnemyBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyBase), 563321352U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_2217747603(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h__Script_Invisible_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
