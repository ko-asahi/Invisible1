// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/EnemyAIController.h"
#include "Perception/AIPerceptionTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEnemyAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
AIMODULE_API UClass* Z_Construct_UClass_UAIPerceptionComponent_NoRegister();
AIMODULE_API UClass* Z_Construct_UClass_UAISenseConfig_Hearing_NoRegister();
AIMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FAIStimulus();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyAIController();
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyAIController_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AEnemyAIController Function ApplyHearingRangeFromGameState ***************
struct Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Hearing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xbb\x8e\xe6\xb8\xb8\xe6\x88\x8f\xe7\x8a\xb6\xe6\x80\x81\xe8\x8e\xb7\xe5\x8f\x96\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbb\x8e\xe6\xb8\xb8\xe6\x88\x8f\xe7\x8a\xb6\xe6\x80\x81\xe8\x8e\xb7\xe5\x8f\x96\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "ApplyHearingRangeFromGameState", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execApplyHearingRangeFromGameState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyHearingRangeFromGameState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function ApplyHearingRangeFromGameState *****************

// ********** Begin Class AEnemyAIController Function ClearInvestigateRuntimeState *****************
struct Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics
{
	struct EnemyAIController_eventClearInvestigateRuntimeState_Parms
	{
		bool bClearHeardMemory;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Investigate" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// MoveTO \xe5\x90\x8e\xef\xbc\x8c\xe6\xb8\x85\xe9\x99\xa4\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6\xe7\x8a\xb6\xe6\x80\x81\n" },
#endif
		{ "CPP_Default_bClearHeardMemory", "true" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MoveTO \xe5\x90\x8e\xef\xbc\x8c\xe6\xb8\x85\xe9\x99\xa4\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bClearHeardMemory_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearHeardMemory;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::NewProp_bClearHeardMemory_SetBit(void* Obj)
{
	((EnemyAIController_eventClearInvestigateRuntimeState_Parms*)Obj)->bClearHeardMemory = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::NewProp_bClearHeardMemory = { "bClearHeardMemory", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EnemyAIController_eventClearInvestigateRuntimeState_Parms), &Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::NewProp_bClearHeardMemory_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::NewProp_bClearHeardMemory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "ClearInvestigateRuntimeState", Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::EnemyAIController_eventClearInvestigateRuntimeState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::EnemyAIController_eventClearInvestigateRuntimeState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execClearInvestigateRuntimeState)
{
	P_GET_UBOOL(Z_Param_bClearHeardMemory);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearInvestigateRuntimeState(Z_Param_bClearHeardMemory);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function ClearInvestigateRuntimeState *******************

// ********** Begin Class AEnemyAIController Function ExtendInterestHoldTime ***********************
struct Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics
{
	struct EnemyAIController_eventExtendInterestHoldTime_Parms
	{
		float Duration;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Investigate" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbb\xb6\xe9\x95\xbf\xe5\x85\xb4\xe8\xb6\xa3\xe7\x8a\xb6\xe6\x80\x81\xe6\x9c\x80\xe7\x9f\xad\xe4\xbf\x9d\xe6\x8c\x81\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x8c\xe4\xbe\x9b BT Task \xe5\x9c\xa8\xe5\x90\xaf\xe5\x8a\xa8\xe6\x97\xb6\xe6\xb3\xa8\xe5\x85\xa5\xe8\x87\xaa\xe8\xba\xab\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x95\xbf\n// \xe4\xbf\x9d\xe8\xaf\x81 TickDetection \xe7\x9a\x84\xe8\x87\xaa\xe5\x8a\xa8\xe6\xb8\x85\xe7\x90\x86\xe4\xb8\x8d\xe4\xbc\x9a\xe5\x9c\xa8\xe4\xbb\xbb\xe5\x8a\xa1\xe7\xbb\x93\xe6\x9d\x9f\xe5\x89\x8d\xe6\x8f\x90\xe5\x89\x8d\xe8\xa7\xa6\xe5\x8f\x91\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbb\xb6\xe9\x95\xbf\xe5\x85\xb4\xe8\xb6\xa3\xe7\x8a\xb6\xe6\x80\x81\xe6\x9c\x80\xe7\x9f\xad\xe4\xbf\x9d\xe6\x8c\x81\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x8c\xe4\xbe\x9b BT Task \xe5\x9c\xa8\xe5\x90\xaf\xe5\x8a\xa8\xe6\x97\xb6\xe6\xb3\xa8\xe5\x85\xa5\xe8\x87\xaa\xe8\xba\xab\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x95\xbf\n\xe4\xbf\x9d\xe8\xaf\x81 TickDetection \xe7\x9a\x84\xe8\x87\xaa\xe5\x8a\xa8\xe6\xb8\x85\xe7\x90\x86\xe4\xb8\x8d\xe4\xbc\x9a\xe5\x9c\xa8\xe4\xbb\xbb\xe5\x8a\xa1\xe7\xbb\x93\xe6\x9d\x9f\xe5\x89\x8d\xe6\x8f\x90\xe5\x89\x8d\xe8\xa7\xa6\xe5\x8f\x91" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Duration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventExtendInterestHoldTime_Parms, Duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::NewProp_Duration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "ExtendInterestHoldTime", Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::EnemyAIController_eventExtendInterestHoldTime_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::EnemyAIController_eventExtendInterestHoldTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execExtendInterestHoldTime)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Duration);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ExtendInterestHoldTime(Z_Param_Duration);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function ExtendInterestHoldTime *************************

// ********** Begin Class AEnemyAIController Function GetAlertness *********************************
struct Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics
{
	struct EnemyAIController_eventGetAlertness_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Alert" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\x8e\xb7\xe5\x8f\x96\xe5\xae\x9e\xe9\x99\x85\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x8e\xb7\xe5\x8f\x96\xe5\xae\x9e\xe9\x99\x85\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventGetAlertness_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "GetAlertness", Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::EnemyAIController_eventGetAlertness_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::EnemyAIController_eventGetAlertness_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_GetAlertness()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_GetAlertness_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execGetAlertness)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetAlertness();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function GetAlertness ***********************************

// ********** Begin Class AEnemyAIController Function GetAlertnessNormalized ***********************
struct Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics
{
	struct EnemyAIController_eventGetAlertnessNormalized_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Alert" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\x8e\xb7\xe5\x8f\x96\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe7\x99\xbe\xe5\x88\x86\xe6\xaf\x94\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x8e\xb7\xe5\x8f\x96\xe8\xad\xa6\xe6\x88\x92\xe5\x80\xbc\xe7\x99\xbe\xe5\x88\x86\xe6\xaf\x94" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventGetAlertnessNormalized_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "GetAlertnessNormalized", Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::EnemyAIController_eventGetAlertnessNormalized_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::EnemyAIController_eventGetAlertnessNormalized_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execGetAlertnessNormalized)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetAlertnessNormalized();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function GetAlertnessNormalized *************************

// ********** Begin Class AEnemyAIController Function GetHearingRange ******************************
struct Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics
{
	struct EnemyAIController_eventGetHearingRange_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Hearing" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventGetHearingRange_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "GetHearingRange", Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::EnemyAIController_eventGetHearingRange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::EnemyAIController_eventGetHearingRange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_GetHearingRange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_GetHearingRange_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execGetHearingRange)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetHearingRange();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function GetHearingRange ********************************

// ********** Begin Class AEnemyAIController Function HandleGlobalHearingRangeChanged **************
struct Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics
{
	struct EnemyAIController_eventHandleGlobalHearingRangeChanged_Parms
	{
		float NewRange;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa4\x84\xe7\x90\x86\xe5\x85\xa8\xe5\xb1\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe5\x8f\x98\xe5\x8c\x96\xe7\x9a\x84\xe5\x9b\x9e\xe8\xb0\x83\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\x84\xe7\x90\x86\xe5\x85\xa8\xe5\xb1\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe5\x8f\x98\xe5\x8c\x96\xe7\x9a\x84\xe5\x9b\x9e\xe8\xb0\x83" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::NewProp_NewRange = { "NewRange", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventHandleGlobalHearingRangeChanged_Parms, NewRange), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::NewProp_NewRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "HandleGlobalHearingRangeChanged", Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::EnemyAIController_eventHandleGlobalHearingRangeChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::EnemyAIController_eventHandleGlobalHearingRangeChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execHandleGlobalHearingRangeChanged)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewRange);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleGlobalHearingRangeChanged(Z_Param_NewRange);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function HandleGlobalHearingRangeChanged ****************

// ********** Begin Class AEnemyAIController Function OnTargetPerceptionUpdated ********************
struct Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics
{
	struct EnemyAIController_eventOnTargetPerceptionUpdated_Parms
	{
		AActor* Actor;
		FAIStimulus Stimulus;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x90\xac\xe5\x88\xb0\xe5\xa3\xb0\xe9\x9f\xb3\xe7\x9a\x84\xe5\x9b\x9e\xe8\xb0\x83\xef\xbc\x88\xe7\x9b\xb4\xe6\x8e\xa5\xe6\x8e\xa5\xe6\x94\xb6 FAIStimulus\xef\xbc\x8c\xe6\xaf\x94 OnPerceptionUpdated+GetActorsPerception \xe6\x9b\xb4\xe5\x8f\xaf\xe9\x9d\xa0\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\xac\xe5\x88\xb0\xe5\xa3\xb0\xe9\x9f\xb3\xe7\x9a\x84\xe5\x9b\x9e\xe8\xb0\x83\xef\xbc\x88\xe7\x9b\xb4\xe6\x8e\xa5\xe6\x8e\xa5\xe6\x94\xb6 FAIStimulus\xef\xbc\x8c\xe6\xaf\x94 OnPerceptionUpdated+GetActorsPerception \xe6\x9b\xb4\xe5\x8f\xaf\xe9\x9d\xa0\xef\xbc\x89" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Stimulus;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventOnTargetPerceptionUpdated_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::NewProp_Stimulus = { "Stimulus", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventOnTargetPerceptionUpdated_Parms, Stimulus), Z_Construct_UScriptStruct_FAIStimulus, METADATA_PARAMS(0, nullptr) }; // 1267494880
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::NewProp_Stimulus,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "OnTargetPerceptionUpdated", Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::EnemyAIController_eventOnTargetPerceptionUpdated_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::EnemyAIController_eventOnTargetPerceptionUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execOnTargetPerceptionUpdated)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_GET_STRUCT(FAIStimulus,Z_Param_Stimulus);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnTargetPerceptionUpdated(Z_Param_Actor,Z_Param_Stimulus);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function OnTargetPerceptionUpdated **********************

// ********** Begin Class AEnemyAIController Function SetAIPaused **********************************
struct Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics
{
	struct EnemyAIController_eventSetAIPaused_Parms
	{
		bool bPaused;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x9a\x82\xe5\x81\x9c\xe8\xa7\x92\xe8\x89\xb2\xef\xbc\x8c\xe4\xbe\x9b\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x88\x87\xe6\x8d\xa2\xe6\x97\xb6\xe8\xb0\x83\xe7\x94\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9a\x82\xe5\x81\x9c\xe8\xa7\x92\xe8\x89\xb2\xef\xbc\x8c\xe4\xbe\x9b\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x88\x87\xe6\x8d\xa2\xe6\x97\xb6\xe8\xb0\x83\xe7\x94\xa8" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bPaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPaused;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::NewProp_bPaused_SetBit(void* Obj)
{
	((EnemyAIController_eventSetAIPaused_Parms*)Obj)->bPaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::NewProp_bPaused = { "bPaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EnemyAIController_eventSetAIPaused_Parms), &Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::NewProp_bPaused_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::NewProp_bPaused,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "SetAIPaused", Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::EnemyAIController_eventSetAIPaused_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::EnemyAIController_eventSetAIPaused_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_SetAIPaused()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_SetAIPaused_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execSetAIPaused)
{
	P_GET_UBOOL(Z_Param_bPaused);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAIPaused(Z_Param_bPaused);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function SetAIPaused ************************************

// ********** Begin Class AEnemyAIController Function SetInjectedPath ******************************
struct Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics
{
	struct EnemyAIController_eventSetInjectedPath_Parms
	{
		TArray<FVector> InPathPoints;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|InjectedPath" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xae\xbe\xe7\xbd\xae\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe7\xbb\x98\xe5\x88\xb6\xe5\x90\x8e\xe7\x9a\x84\xe4\xb8\xb4\xe6\x97\xb6\xe8\xb7\xaf\xe5\xbe\x84\xef\xbc\x88\xe9\x80\x80\xe5\x87\xba\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x90\x8e\xe6\x89\xa7\xe8\xa1\x8c\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xae\xbe\xe7\xbd\xae\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe7\xbb\x98\xe5\x88\xb6\xe5\x90\x8e\xe7\x9a\x84\xe4\xb8\xb4\xe6\x97\xb6\xe8\xb7\xaf\xe5\xbe\x84\xef\xbc\x88\xe9\x80\x80\xe5\x87\xba\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x90\x8e\xe6\x89\xa7\xe8\xa1\x8c\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InPathPoints_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InPathPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InPathPoints;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::NewProp_InPathPoints_Inner = { "InPathPoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::NewProp_InPathPoints = { "InPathPoints", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventSetInjectedPath_Parms, InPathPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InPathPoints_MetaData), NewProp_InPathPoints_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::NewProp_InPathPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::NewProp_InPathPoints,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "SetInjectedPath", Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::PropPointers), sizeof(Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::EnemyAIController_eventSetInjectedPath_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::EnemyAIController_eventSetInjectedPath_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_SetInjectedPath()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_SetInjectedPath_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execSetInjectedPath)
{
	P_GET_TARRAY_REF(FVector,Z_Param_Out_InPathPoints);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetInjectedPath(Z_Param_Out_InPathPoints);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function SetInjectedPath ********************************

// ********** Begin Class AEnemyAIController Function StartDetectionTimer **************************
struct Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x90\xaf\xe7\x94\xa8\xe8\xa7\x86\xe8\xa7\x89\xe6\x9c\xba\xe5\x88\xb6\xef\xbc\x8c\xe5\x8f\xaf\xe5\x9c\xa8\xe7\xbb\x93\xe6\x9d\x9f\xe6\x9a\x82\xe5\x81\x9c\xef\xbc\x8c\xe4\xbe\x9b\xe6\x81\xa2\xe5\xa4\x8d\xe6\x97\xb6\xe8\xb0\x83\xe7\x94\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\xaf\xe7\x94\xa8\xe8\xa7\x86\xe8\xa7\x89\xe6\x9c\xba\xe5\x88\xb6\xef\xbc\x8c\xe5\x8f\xaf\xe5\x9c\xa8\xe7\xbb\x93\xe6\x9d\x9f\xe6\x9a\x82\xe5\x81\x9c\xef\xbc\x8c\xe4\xbe\x9b\xe6\x81\xa2\xe5\xa4\x8d\xe6\x97\xb6\xe8\xb0\x83\xe7\x94\xa8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "StartDetectionTimer", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execStartDetectionTimer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartDetectionTimer();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function StartDetectionTimer ****************************

// ********** Begin Class AEnemyAIController *******************************************************
void AEnemyAIController::StaticRegisterNativesAEnemyAIController()
{
	UClass* Class = AEnemyAIController::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ApplyHearingRangeFromGameState", &AEnemyAIController::execApplyHearingRangeFromGameState },
		{ "ClearInvestigateRuntimeState", &AEnemyAIController::execClearInvestigateRuntimeState },
		{ "ExtendInterestHoldTime", &AEnemyAIController::execExtendInterestHoldTime },
		{ "GetAlertness", &AEnemyAIController::execGetAlertness },
		{ "GetAlertnessNormalized", &AEnemyAIController::execGetAlertnessNormalized },
		{ "GetHearingRange", &AEnemyAIController::execGetHearingRange },
		{ "HandleGlobalHearingRangeChanged", &AEnemyAIController::execHandleGlobalHearingRangeChanged },
		{ "OnTargetPerceptionUpdated", &AEnemyAIController::execOnTargetPerceptionUpdated },
		{ "SetAIPaused", &AEnemyAIController::execSetAIPaused },
		{ "SetInjectedPath", &AEnemyAIController::execSetInjectedPath },
		{ "StartDetectionTimer", &AEnemyAIController::execStartDetectionTimer },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AEnemyAIController;
UClass* AEnemyAIController::GetPrivateStaticClass()
{
	using TClass = AEnemyAIController;
	if (!Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("EnemyAIController"),
			Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton,
			StaticRegisterNativesAEnemyAIController,
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
	return Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton;
}
UClass* Z_Construct_UClass_AEnemyAIController_NoRegister()
{
	return AEnemyAIController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEnemyAIController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\x95\x8c\xe4\xba\xba""AI\xe6\x8e\xa7\xe5\x88\xb6\xe5\x99\xa8\xef\xbc\x8c\xe8\xb4\x9f\xe8\xb4\xa3\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84""AI\xe8\xa1\x8c\xe4\xb8\xba\xe5\x92\x8c\xe6\x84\x9f\xe7\x9f\xa5\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Enemy/EnemyAIController.h" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba""AI\xe6\x8e\xa7\xe5\x88\xb6\xe5\x99\xa8\xef\xbc\x8c\xe8\xb4\x9f\xe8\xb4\xa3\xe6\x95\x8c\xe4\xba\xba\xe7\x9a\x84""AI\xe8\xa1\x8c\xe4\xb8\xba\xe5\x92\x8c\xe6\x84\x9f\xe7\x9f\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InjectedPathPoints_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x8f\x92\xe5\x85\xa5\xe8\xb7\xaf\xe5\xbe\x84\xe7\x82\xb9\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8f\x92\xe5\x85\xa5\xe8\xb7\xaf\xe5\xbe\x84\xe7\x82\xb9" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetectionInterval_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "AI|Perception" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.02" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x86\xe8\xa7\x89\xe6\xa3\x80\xe6\xb5\x8b\xe9\xa2\x91\xe7\x8e\x87\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe8\xa7\x89\xe6\xa3\x80\xe6\xb5\x8b\xe9\xa2\x91\xe7\x8e\x87\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
		{ "UIMax", "0.5" },
		{ "UIMin", "0.02" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingRange_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x90\xac\xe8\xa7\x89\xe5\x8d\x8a\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\xac\xe8\xa7\x89\xe5\x8d\x8a\xe5\xbe\x84" },
#endif
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingMaxAge_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xb8\xa2\xe5\xa4\xb1\xe5\x88\xba\xe6\xbf\x80\xe5\x90\x8e\xe7\x9a\x84\xe4\xbf\x9d\xe7\x95\x99\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xb8\xa2\xe5\xa4\xb1\xe5\x88\xba\xe6\xbf\x80\xe5\x90\x8e\xe7\x9a\x84\xe4\xbf\x9d\xe7\x95\x99\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
		{ "UIMax", "10.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseLoSHearing_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xaf\xe5\x90\xa6\xe9\x9c\x80\xe8\xa6\x81\xe8\xa7\x86\xe7\xba\xbf\xe6\x89\x8d\xe2\x80\x9c\xe5\x90\xac\xe5\x88\xb0\xe2\x80\x9d\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe9\x9c\x80\xe8\xa6\x81\xe8\xa7\x86\xe7\xba\xbf\xe6\x89\x8d\xe2\x80\x9c\xe5\x90\xac\xe5\x88\xb0\xe2\x80\x9d" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableHearing_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe7\x94\xa8\xe5\x90\xac\xe8\xa7\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe7\x94\xa8\xe5\x90\xac\xe8\xa7\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerceptionComp_MetaData[] = {
		{ "Category", "EnemyAIController" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x84\x9f\xe7\x9f\xa5\xe7\xbb\x84\xe4\xbb\xb6\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x84\x9f\xe7\x9f\xa5\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingConfig_MetaData[] = {
		{ "Category", "EnemyAIController" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x90\xac\xe8\xa7\x89\xe6\xa3\x80\xe6\xb5\x8b\xe9\x85\x8d\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\xac\xe8\xa7\x89\xe6\xa3\x80\xe6\xb5\x8b\xe9\x85\x8d\xe7\xbd\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InjectedPathPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InjectedPathPoints;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DetectionInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HearingRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HearingMaxAge;
	static void NewProp_bUseLoSHearing_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseLoSHearing;
	static void NewProp_bEnableHearing_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableHearing;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PerceptionComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HearingConfig;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyAIController_ApplyHearingRangeFromGameState, "ApplyHearingRangeFromGameState" }, // 1782712423
		{ &Z_Construct_UFunction_AEnemyAIController_ClearInvestigateRuntimeState, "ClearInvestigateRuntimeState" }, // 1286704388
		{ &Z_Construct_UFunction_AEnemyAIController_ExtendInterestHoldTime, "ExtendInterestHoldTime" }, // 3670444304
		{ &Z_Construct_UFunction_AEnemyAIController_GetAlertness, "GetAlertness" }, // 1564541221
		{ &Z_Construct_UFunction_AEnemyAIController_GetAlertnessNormalized, "GetAlertnessNormalized" }, // 3592982294
		{ &Z_Construct_UFunction_AEnemyAIController_GetHearingRange, "GetHearingRange" }, // 639232245
		{ &Z_Construct_UFunction_AEnemyAIController_HandleGlobalHearingRangeChanged, "HandleGlobalHearingRangeChanged" }, // 496205932
		{ &Z_Construct_UFunction_AEnemyAIController_OnTargetPerceptionUpdated, "OnTargetPerceptionUpdated" }, // 3642150558
		{ &Z_Construct_UFunction_AEnemyAIController_SetAIPaused, "SetAIPaused" }, // 2266124347
		{ &Z_Construct_UFunction_AEnemyAIController_SetInjectedPath, "SetInjectedPath" }, // 2467395741
		{ &Z_Construct_UFunction_AEnemyAIController_StartDetectionTimer, "StartDetectionTimer" }, // 1625160672
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_InjectedPathPoints_Inner = { "InjectedPathPoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_InjectedPathPoints = { "InjectedPathPoints", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, InjectedPathPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InjectedPathPoints_MetaData), NewProp_InjectedPathPoints_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_DetectionInterval = { "DetectionInterval", nullptr, (EPropertyFlags)0x0040000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, DetectionInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetectionInterval_MetaData), NewProp_DetectionInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingRange = { "HearingRange", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, HearingRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingRange_MetaData), NewProp_HearingRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingMaxAge = { "HearingMaxAge", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, HearingMaxAge), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingMaxAge_MetaData), NewProp_HearingMaxAge_MetaData) };
void Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bUseLoSHearing_SetBit(void* Obj)
{
	((AEnemyAIController*)Obj)->bUseLoSHearing = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bUseLoSHearing = { "bUseLoSHearing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AEnemyAIController), &Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bUseLoSHearing_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseLoSHearing_MetaData), NewProp_bUseLoSHearing_MetaData) };
void Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bEnableHearing_SetBit(void* Obj)
{
	((AEnemyAIController*)Obj)->bEnableHearing = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bEnableHearing = { "bEnableHearing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AEnemyAIController), &Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bEnableHearing_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableHearing_MetaData), NewProp_bEnableHearing_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_PerceptionComp = { "PerceptionComp", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, PerceptionComp), Z_Construct_UClass_UAIPerceptionComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerceptionComp_MetaData), NewProp_PerceptionComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingConfig = { "HearingConfig", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, HearingConfig), Z_Construct_UClass_UAISenseConfig_Hearing_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingConfig_MetaData), NewProp_HearingConfig_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyAIController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_InjectedPathPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_InjectedPathPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_DetectionInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingMaxAge,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bUseLoSHearing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_bEnableHearing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_PerceptionComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingConfig,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AEnemyAIController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyAIController_Statics::ClassParams = {
	&AEnemyAIController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AEnemyAIController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::PropPointers),
	0,
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyAIController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyAIController()
{
	if (!Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton, Z_Construct_UClass_AEnemyAIController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyAIController);
AEnemyAIController::~AEnemyAIController() {}
// ********** End Class AEnemyAIController *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyAIController, AEnemyAIController::StaticClass, TEXT("AEnemyAIController"), &Z_Registration_Info_UClass_AEnemyAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyAIController), 3889637823U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h__Script_Invisible_3496040586(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
