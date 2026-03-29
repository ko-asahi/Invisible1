// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Task/BTTask_FaceTarget.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBTTask_FaceTarget() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
AIMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FBlackboardKeySelector();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_FaceTarget();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_FaceTarget_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBTTask_FaceTarget *******************************************************
void UBTTask_FaceTarget::StaticRegisterNativesUBTTask_FaceTarget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBTTask_FaceTarget;
UClass* UBTTask_FaceTarget::GetPrivateStaticClass()
{
	using TClass = UBTTask_FaceTarget;
	if (!Z_Registration_Info_UClass_UBTTask_FaceTarget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BTTask_FaceTarget"),
			Z_Registration_Info_UClass_UBTTask_FaceTarget.InnerSingleton,
			StaticRegisterNativesUBTTask_FaceTarget,
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
	return Z_Registration_Info_UClass_UBTTask_FaceTarget.InnerSingleton;
}
UClass* Z_Construct_UClass_UBTTask_FaceTarget_NoRegister()
{
	return UBTTask_FaceTarget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBTTask_FaceTarget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Task/BTTask_FaceTarget.h" },
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VisualTargetActorKey_MetaData[] = {
		{ "Category", "Blackboard" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xae\x9e\xe6\x97\xb6\xe8\xa7\x86\xe8\xa7\x89\xe7\x9b\xae\xe6\xa0\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xae\x9e\xe6\x97\xb6\xe8\xa7\x86\xe8\xa7\x89\xe7\x9b\xae\xe6\xa0\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastSeenLocationKey_MetaData[] = {
		{ "Category", "Blackboard" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa4\xb1\xe5\x8e\xbb\xe7\x9b\xae\xe6\xa0\x87\xe6\x97\xb6\xef\xbc\x8c\xe5\x9b\x9e\xe9\x80\x80\xe5\x88\xb0\xe6\x9c\x80\xe5\x90\x8e\xe7\x9b\xae\xe5\x87\xbb\xe7\x82\xb9\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\xb1\xe5\x8e\xbb\xe7\x9b\xae\xe6\xa0\x87\xe6\x97\xb6\xef\xbc\x8c\xe5\x9b\x9e\xe9\x80\x80\xe5\x88\xb0\xe6\x9c\x80\xe5\x90\x8e\xe7\x9b\xae\xe5\x87\xbb\xe7\x82\xb9" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnSpeed_MetaData[] = {
		{ "Category", "Face" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x86\xe8\xa7\x92\xe8\xbd\xac\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe8\xa7\x92\xe8\xbd\xac\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AcceptYawError_MetaData[] = {
		{ "Category", "Face" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xaf\xaf\xe5\xb7\xae\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xaf\xaf\xe5\xb7\xae\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterestLocationKey_MetaData[] = {
		{ "Category", "Blackboard" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9c\x8b\xe5\x88\xb0\xe6\x88\x96\xe5\x90\xac\xe5\x88\xb0\xe7\x9a\x84\xe9\xa6\x96\xe6\xac\xa1\xe4\xbd\x8d\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9c\x8b\xe5\x88\xb0\xe6\x88\x96\xe5\x90\xac\xe5\x88\xb0\xe7\x9a\x84\xe9\xa6\x96\xe6\xac\xa1\xe4\xbd\x8d\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceDuration_MetaData[] = {
		{ "Category", "Face" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9c\x8b\xe5\x90\x91\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9c\x8b\xe5\x90\x91\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bTrackTargetDuringFace_MetaData[] = {
		{ "Category", "Face" },
		{ "ModuleRelativePath", "Public/Task/BTTask_FaceTarget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_VisualTargetActorKey;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LastSeenLocationKey;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TurnSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AcceptYawError;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InterestLocationKey;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FaceDuration;
	static void NewProp_bTrackTargetDuringFace_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bTrackTargetDuringFace;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_FaceTarget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_VisualTargetActorKey = { "VisualTargetActorKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, VisualTargetActorKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VisualTargetActorKey_MetaData), NewProp_VisualTargetActorKey_MetaData) }; // 815030858
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_LastSeenLocationKey = { "LastSeenLocationKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, LastSeenLocationKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastSeenLocationKey_MetaData), NewProp_LastSeenLocationKey_MetaData) }; // 815030858
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_TurnSpeed = { "TurnSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, TurnSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnSpeed_MetaData), NewProp_TurnSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_AcceptYawError = { "AcceptYawError", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, AcceptYawError), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AcceptYawError_MetaData), NewProp_AcceptYawError_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_InterestLocationKey = { "InterestLocationKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, InterestLocationKey), Z_Construct_UScriptStruct_FBlackboardKeySelector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterestLocationKey_MetaData), NewProp_InterestLocationKey_MetaData) }; // 815030858
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_FaceDuration = { "FaceDuration", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_FaceTarget, FaceDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceDuration_MetaData), NewProp_FaceDuration_MetaData) };
void Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_bTrackTargetDuringFace_SetBit(void* Obj)
{
	((UBTTask_FaceTarget*)Obj)->bTrackTargetDuringFace = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_bTrackTargetDuringFace = { "bTrackTargetDuringFace", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UBTTask_FaceTarget), &Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_bTrackTargetDuringFace_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bTrackTargetDuringFace_MetaData), NewProp_bTrackTargetDuringFace_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTTask_FaceTarget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_VisualTargetActorKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_LastSeenLocationKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_TurnSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_AcceptYawError,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_InterestLocationKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_FaceDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_FaceTarget_Statics::NewProp_bTrackTargetDuringFace,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_FaceTarget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBTTask_FaceTarget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_FaceTarget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_FaceTarget_Statics::ClassParams = {
	&UBTTask_FaceTarget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBTTask_FaceTarget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_FaceTarget_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_FaceTarget_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_FaceTarget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBTTask_FaceTarget()
{
	if (!Z_Registration_Info_UClass_UBTTask_FaceTarget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_FaceTarget.OuterSingleton, Z_Construct_UClass_UBTTask_FaceTarget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBTTask_FaceTarget.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_FaceTarget);
UBTTask_FaceTarget::~UBTTask_FaceTarget() {}
// ********** End Class UBTTask_FaceTarget *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_FaceTarget_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_FaceTarget, UBTTask_FaceTarget::StaticClass, TEXT("UBTTask_FaceTarget"), &Z_Registration_Info_UClass_UBTTask_FaceTarget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_FaceTarget), 1282812667U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_FaceTarget_h__Script_Invisible_3570058157(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_FaceTarget_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_FaceTarget_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
