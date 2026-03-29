// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Task/BTTask_ClearInvestigateState.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBTTask_ClearInvestigateState() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
AIMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FBlackboardKeySelector();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_ClearInvestigateState();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_ClearInvestigateState_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBTTask_ClearInvestigateState ********************************************
void UBTTask_ClearInvestigateState::StaticRegisterNativesUBTTask_ClearInvestigateState()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBTTask_ClearInvestigateState;
UClass* UBTTask_ClearInvestigateState::GetPrivateStaticClass()
{
	using TClass = UBTTask_ClearInvestigateState;
	if (!Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BTTask_ClearInvestigateState"),
			Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.InnerSingleton,
			StaticRegisterNativesUBTTask_ClearInvestigateState,
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
	return Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.InnerSingleton;
}
UClass* Z_Construct_UClass_UBTTask_ClearInvestigateState_NoRegister()
{
	return UBTTask_ClearInvestigateState::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * MoveTo \xe5\x90\x8e\xef\xbc\x8c\xe6\xb8\x85\xe9\x99\xa4\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6\xe7\x8a\xb6\xe6\x80\x81\n */" },
#endif
		{ "IncludePath", "Task/BTTask_ClearInvestigateState.h" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MoveTo \xe5\x90\x8e\xef\xbc\x8c\xe6\xb8\x85\xe9\x99\xa4\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HasInterestKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsInvestigatingKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterestLocationKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeardLocationKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VisualTargetActorKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsChasingKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlertnessKey_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClearInterestLocation_MetaData[] = {
		{ "Category", "Options" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClearHeardLocation_MetaData[] = {
		{ "Category", "Options" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClearVisualTargetActor_MetaData[] = {
		{ "Category", "Options" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClearControllerRuntimeMemory_MetaData[] = {
		{ "Category", "Options" },
		{ "ModuleRelativePath", "Public/Task/BTTask_ClearInvestigateState.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_HasInterestKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IsInvestigatingKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InterestLocationKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HeardLocationKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VisualTargetActorKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IsChasingKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AlertnessKey;
	static void NewProp_bClearInterestLocation_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearInterestLocation;
	static void NewProp_bClearHeardLocation_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearHeardLocation;
	static void NewProp_bClearVisualTargetActor_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearVisualTargetActor;
	static void NewProp_bClearControllerRuntimeMemory_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClearControllerRuntimeMemory;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_ClearInvestigateState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_HasInterestKey = { "HasInterestKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, HasInterestKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HasInterestKey_MetaData), NewProp_HasInterestKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_IsInvestigatingKey = { "IsInvestigatingKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, IsInvestigatingKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsInvestigatingKey_MetaData), NewProp_IsInvestigatingKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_InterestLocationKey = { "InterestLocationKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, InterestLocationKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterestLocationKey_MetaData), NewProp_InterestLocationKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_HeardLocationKey = { "HeardLocationKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, HeardLocationKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeardLocationKey_MetaData), NewProp_HeardLocationKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_VisualTargetActorKey = { "VisualTargetActorKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, VisualTargetActorKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VisualTargetActorKey_MetaData), NewProp_VisualTargetActorKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_IsChasingKey = { "IsChasingKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, IsChasingKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsChasingKey_MetaData), NewProp_IsChasingKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_AlertnessKey = { "AlertnessKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_ClearInvestigateState, AlertnessKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlertnessKey_MetaData), NewProp_AlertnessKey_MetaData) }; // 815030858
void Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearInterestLocation_SetBit(void* Obj)
{
	((UBTTask_ClearInvestigateState*)Obj)->bClearInterestLocation = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearInterestLocation = { "bClearInterestLocation", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UBTTask_ClearInvestigateState), &Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearInterestLocation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClearInterestLocation_MetaData), NewProp_bClearInterestLocation_MetaData) };
void Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearHeardLocation_SetBit(void* Obj)
{
	((UBTTask_ClearInvestigateState*)Obj)->bClearHeardLocation = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearHeardLocation = { "bClearHeardLocation", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UBTTask_ClearInvestigateState), &Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearHeardLocation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClearHeardLocation_MetaData), NewProp_bClearHeardLocation_MetaData) };
void Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearVisualTargetActor_SetBit(void* Obj)
{
	((UBTTask_ClearInvestigateState*)Obj)->bClearVisualTargetActor = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearVisualTargetActor = { "bClearVisualTargetActor", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UBTTask_ClearInvestigateState), &Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearVisualTargetActor_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClearVisualTargetActor_MetaData), NewProp_bClearVisualTargetActor_MetaData) };
void Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearControllerRuntimeMemory_SetBit(void* Obj)
{
	((UBTTask_ClearInvestigateState*)Obj)->bClearControllerRuntimeMemory = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearControllerRuntimeMemory = { "bClearControllerRuntimeMemory", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UBTTask_ClearInvestigateState), &Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearControllerRuntimeMemory_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClearControllerRuntimeMemory_MetaData), NewProp_bClearControllerRuntimeMemory_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_HasInterestKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_IsInvestigatingKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_InterestLocationKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_HeardLocationKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_VisualTargetActorKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_IsChasingKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_AlertnessKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearInterestLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearHeardLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearVisualTargetActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::NewProp_bClearControllerRuntimeMemory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::ClassParams = {
	&UBTTask_ClearInvestigateState::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBTTask_ClearInvestigateState()
{
	if (!Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.OuterSingleton, Z_Construct_UClass_UBTTask_ClearInvestigateState_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBTTask_ClearInvestigateState.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_ClearInvestigateState);
UBTTask_ClearInvestigateState::~UBTTask_ClearInvestigateState() {}
// ********** End Class UBTTask_ClearInvestigateState **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_ClearInvestigateState_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_ClearInvestigateState, UBTTask_ClearInvestigateState::StaticClass, TEXT("UBTTask_ClearInvestigateState"), &Z_Registration_Info_UClass_UBTTask_ClearInvestigateState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_ClearInvestigateState), 954912246U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_ClearInvestigateState_h__Script_Invisible_2048463102(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_ClearInvestigateState_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_ClearInvestigateState_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
