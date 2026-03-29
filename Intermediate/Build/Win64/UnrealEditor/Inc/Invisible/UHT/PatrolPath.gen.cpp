// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/PatrolPath.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePatrolPath() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_APatrolPath();
INVISIBLE_API UClass* Z_Construct_UClass_APatrolPath_NoRegister();
INVISIBLE_API UEnum* Z_Construct_UEnum_Invisible_EWaypointBehavior();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FPatrolWaypointData();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FWaypointBinding();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FWaypointBinding **************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FWaypointBinding;
class UScriptStruct* FWaypointBinding::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FWaypointBinding.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FWaypointBinding.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FWaypointBinding, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("WaypointBinding"));
	}
	return Z_Registration_Info_UScriptStruct_FWaypointBinding.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FWaypointBinding_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xbb\x91\xe5\xae\x9a\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\xbb\x91\xe5\xae\x9a\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FWaypointBinding>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FWaypointBinding_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"WaypointBinding",
	nullptr,
	0,
	sizeof(FWaypointBinding),
	alignof(FWaypointBinding),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaypointBinding_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FWaypointBinding_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FWaypointBinding()
{
	if (!Z_Registration_Info_UScriptStruct_FWaypointBinding.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FWaypointBinding.InnerSingleton, Z_Construct_UScriptStruct_FWaypointBinding_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FWaypointBinding.InnerSingleton;
}
// ********** End ScriptStruct FWaypointBinding ****************************************************

// ********** Begin ScriptStruct FPatrolWaypointData ***********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FPatrolWaypointData;
class UScriptStruct* FPatrolWaypointData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FPatrolWaypointData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FPatrolWaypointData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPatrolWaypointData, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("PatrolWaypointData"));
	}
	return Z_Registration_Info_UScriptStruct_FPatrolWaypointData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FPatrolWaypointData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe4\xbf\xa1\xe6\x81\xaf\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe4\xbf\xa1\xe6\x81\xaf\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Point_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Behavior_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaitTime_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x81\x9c\xe7\x95\x99\xe6\x97\xb6\xe9\x97\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x81\x9c\xe7\x95\x99\xe6\x97\xb6\xe9\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAngle_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// EWaypointBehavior \xe4\xb8\xba LookAround \xe6\x97\xb6\xef\xbc\x8c\xe6\xbf\x80\xe6\xb4\xbb\n// \xe6\x89\xab\xe8\xa7\x86\xe8\xa7\x92\xe5\xba\xa6\n" },
#endif
		{ "EditCondition", "Behavior == EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "EWaypointBehavior \xe4\xb8\xba LookAround \xe6\x97\xb6\xef\xbc\x8c\xe6\xbf\x80\xe6\xb4\xbb\n\xe6\x89\xab\xe8\xa7\x86\xe8\xa7\x92\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookSpeed_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x89\xab\xe8\xa7\x86\xe9\x80\x9f\xe5\xba\xa6\xef\xbc\x88\xe5\xba\xa6/\xe7\xa7\x92\xef\xbc\x89\n" },
#endif
		{ "EditCondition", "Behavior == EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x89\xab\xe8\xa7\x86\xe9\x80\x9f\xe5\xba\xa6\xef\xbc\x88\xe5\xba\xa6/\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseCustomLookCenter_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xaf\xe5\x90\xa6\xe4\xbd\xbf\xe7\x94\xa8\xe8\x87\xaa\xe5\xae\x9a\xe4\xb9\x89\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xef\xbc\x88\xe4\xbb\xa5\xe8\xaf\xa5\xe8\x8a\x82\xe7\x82\xb9\xe7\xae\xad\xe5\xa4\xb4\xe7\xbb\x84\xe4\xbb\xb6\xe7\x9a\x84\xe6\x9c\x9d\xe5\x90\x91\xe4\xbd\x9c\xe4\xb8\xba\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xef\xbc\x89\n" },
#endif
		{ "EditCondition", "Behavior == EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe4\xbd\xbf\xe7\x94\xa8\xe8\x87\xaa\xe5\xae\x9a\xe4\xb9\x89\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xef\xbc\x88\xe4\xbb\xa5\xe8\xaf\xa5\xe8\x8a\x82\xe7\x82\xb9\xe7\xae\xad\xe5\xa4\xb4\xe7\xbb\x84\xe4\xbb\xb6\xe7\x9a\x84\xe6\x9c\x9d\xe5\x90\x91\xe4\xbd\x9c\xe4\xb8\xba\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookCenterYawOffset_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9c\xa8\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x9f\xba\xe7\xa1\x80\xe4\xb8\x8a\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89\n" },
#endif
		{ "EditCondition", "Behavior == EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9c\xa8\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x9f\xba\xe7\xa1\x80\xe4\xb8\x8a\xe5\x81\x8f\xe7\xa7\xbb\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreLookPauseTime_MetaData[] = {
		{ "Category", "PatrolWaypointData" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x89\xa7\xe8\xa1\x8c\xe6\x89\xab\xe8\xa7\x86\xe6\x97\xb6\xef\xbc\x8c\xe9\x9d\x99\xe6\xad\xa2\xe5\xa4\x9a\xe4\xb9\x85\xef\xbc\x88\xe5\xbc\x80\xe5\x90\xaf\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x88\x99\xe4\xb8\xba\xe8\xbd\xac\xe5\x88\xb0\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x90\x8e\xef\xbc\x89\xe5\x86\x8d\xe5\xbc\x80\xe5\xa7\x8b\xe5\xb7\xa6\xe5\x8f\xb3\xe8\xbd\xac\xe5\x90\x91\n" },
#endif
		{ "EditCondition", "Behavior == EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x89\xa7\xe8\xa1\x8c\xe6\x89\xab\xe8\xa7\x86\xe6\x97\xb6\xef\xbc\x8c\xe9\x9d\x99\xe6\xad\xa2\xe5\xa4\x9a\xe4\xb9\x85\xef\xbc\x88\xe5\xbc\x80\xe5\x90\xaf\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x88\x99\xe4\xb8\xba\xe8\xbd\xac\xe5\x88\xb0\xe4\xb8\xad\xe8\xbd\xb4\xe7\xba\xbf\xe5\x90\x8e\xef\xbc\x89\xe5\x86\x8d\xe5\xbc\x80\xe5\xa7\x8b\xe5\xb7\xa6\xe5\x8f\xb3\xe8\xbd\xac\xe5\x90\x91" },
#endif
		{ "UIMax", "5.0" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Point;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Behavior_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Behavior;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaitTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LookAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LookSpeed;
	static void NewProp_bUseCustomLookCenter_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseCustomLookCenter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LookCenterYawOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PreLookPauseTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPatrolWaypointData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Point = { "Point", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, Point), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Point_MetaData), NewProp_Point_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Behavior_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Behavior = { "Behavior", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, Behavior), Z_Construct_UEnum_Invisible_EWaypointBehavior, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Behavior_MetaData), NewProp_Behavior_MetaData) }; // 3700645603
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_WaitTime = { "WaitTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, WaitTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaitTime_MetaData), NewProp_WaitTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookAngle = { "LookAngle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, LookAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAngle_MetaData), NewProp_LookAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookSpeed = { "LookSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, LookSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookSpeed_MetaData), NewProp_LookSpeed_MetaData) };
void Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_bUseCustomLookCenter_SetBit(void* Obj)
{
	((FPatrolWaypointData*)Obj)->bUseCustomLookCenter = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_bUseCustomLookCenter = { "bUseCustomLookCenter", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FPatrolWaypointData), &Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_bUseCustomLookCenter_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseCustomLookCenter_MetaData), NewProp_bUseCustomLookCenter_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookCenterYawOffset = { "LookCenterYawOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, LookCenterYawOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookCenterYawOffset_MetaData), NewProp_LookCenterYawOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_PreLookPauseTime = { "PreLookPauseTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPatrolWaypointData, PreLookPauseTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreLookPauseTime_MetaData), NewProp_PreLookPauseTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Point,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Behavior_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_Behavior,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_WaitTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_bUseCustomLookCenter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_LookCenterYawOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewProp_PreLookPauseTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"PatrolWaypointData",
	Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::PropPointers),
	sizeof(FPatrolWaypointData),
	alignof(FPatrolWaypointData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPatrolWaypointData()
{
	if (!Z_Registration_Info_UScriptStruct_FPatrolWaypointData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FPatrolWaypointData.InnerSingleton, Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FPatrolWaypointData.InnerSingleton;
}
// ********** End ScriptStruct FPatrolWaypointData *************************************************

// ********** Begin Class APatrolPath Function HandleWaypointDestroyed *****************************
struct Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics
{
	struct PatrolPath_eventHandleWaypointDestroyed_Parms
	{
		AActor* DestroyedActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DestroyedActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::NewProp_DestroyedActor = { "DestroyedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PatrolPath_eventHandleWaypointDestroyed_Parms, DestroyedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::NewProp_DestroyedActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APatrolPath, nullptr, "HandleWaypointDestroyed", Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PropPointers), sizeof(Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PatrolPath_eventHandleWaypointDestroyed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::Function_MetaDataParams), Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::PatrolPath_eventHandleWaypointDestroyed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APatrolPath::execHandleWaypointDestroyed)
{
	P_GET_OBJECT(AActor,Z_Param_DestroyedActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleWaypointDestroyed(Z_Param_DestroyedActor);
	P_NATIVE_END;
}
// ********** End Class APatrolPath Function HandleWaypointDestroyed *******************************

// ********** Begin Class APatrolPath **************************************************************
void APatrolPath::StaticRegisterNativesAPatrolPath()
{
	UClass* Class = APatrolPath::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HandleWaypointDestroyed", &APatrolPath::execHandleWaypointDestroyed },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APatrolPath;
UClass* APatrolPath::GetPrivateStaticClass()
{
	using TClass = APatrolPath;
	if (!Z_Registration_Info_UClass_APatrolPath.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PatrolPath"),
			Z_Registration_Info_UClass_APatrolPath.InnerSingleton,
			StaticRegisterNativesAPatrolPath,
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
	return Z_Registration_Info_UClass_APatrolPath.InnerSingleton;
}
UClass* Z_Construct_UClass_APatrolPath_NoRegister()
{
	return APatrolPath::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APatrolPath_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Enemy/PatrolPath.h" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Waypoints_MetaData[] = {
		{ "Category", "Patrol" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe6\x95\xb0\xe7\xbb\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe6\x95\xb0\xe7\xbb\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolSpline_MetaData[] = {
		{ "Category", "Patrol" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClosedLoop_MetaData[] = {
		{ "Category", "Patrol" },
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaypointBindings_MetaData[] = {
		{ "ModuleRelativePath", "Public/Enemy/PatrolPath.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Waypoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Waypoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PatrolSpline;
	static void NewProp_bClosedLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClosedLoop;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WaypointBindings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_WaypointBindings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APatrolPath_HandleWaypointDestroyed, "HandleWaypointDestroyed" }, // 1836415892
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APatrolPath>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_Waypoints_Inner = { "Waypoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPatrolWaypointData, METADATA_PARAMS(0, nullptr) }; // 417011989
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_Waypoints = { "Waypoints", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APatrolPath, Waypoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Waypoints_MetaData), NewProp_Waypoints_MetaData) }; // 417011989
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_PatrolSpline = { "PatrolSpline", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APatrolPath, PatrolSpline), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolSpline_MetaData), NewProp_PatrolSpline_MetaData) };
void Z_Construct_UClass_APatrolPath_Statics::NewProp_bClosedLoop_SetBit(void* Obj)
{
	((APatrolPath*)Obj)->bClosedLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_bClosedLoop = { "bClosedLoop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APatrolPath), &Z_Construct_UClass_APatrolPath_Statics::NewProp_bClosedLoop_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClosedLoop_MetaData), NewProp_bClosedLoop_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_WaypointBindings_Inner = { "WaypointBindings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FWaypointBinding, METADATA_PARAMS(0, nullptr) }; // 21874765
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_APatrolPath_Statics::NewProp_WaypointBindings = { "WaypointBindings", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APatrolPath, WaypointBindings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaypointBindings_MetaData), NewProp_WaypointBindings_MetaData) }; // 21874765
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APatrolPath_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_Waypoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_Waypoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_PatrolSpline,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_bClosedLoop,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_WaypointBindings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APatrolPath_Statics::NewProp_WaypointBindings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APatrolPath_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APatrolPath_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APatrolPath_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APatrolPath_Statics::ClassParams = {
	&APatrolPath::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APatrolPath_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APatrolPath_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APatrolPath_Statics::Class_MetaDataParams), Z_Construct_UClass_APatrolPath_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APatrolPath()
{
	if (!Z_Registration_Info_UClass_APatrolPath.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APatrolPath.OuterSingleton, Z_Construct_UClass_APatrolPath_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APatrolPath.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APatrolPath);
APatrolPath::~APatrolPath() {}
// ********** End Class APatrolPath ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FWaypointBinding::StaticStruct, Z_Construct_UScriptStruct_FWaypointBinding_Statics::NewStructOps, TEXT("WaypointBinding"), &Z_Registration_Info_UScriptStruct_FWaypointBinding, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FWaypointBinding), 21874765U) },
		{ FPatrolWaypointData::StaticStruct, Z_Construct_UScriptStruct_FPatrolWaypointData_Statics::NewStructOps, TEXT("PatrolWaypointData"), &Z_Registration_Info_UScriptStruct_FPatrolWaypointData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPatrolWaypointData), 417011989U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APatrolPath, APatrolPath::StaticClass, TEXT("APatrolPath"), &Z_Registration_Info_UClass_APatrolPath, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APatrolPath), 1502837191U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_2017470200(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h__Script_Invisible_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
