// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Task/BTTask_TurnToWaypoint.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBTTask_TurnToWaypoint() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_TurnToWaypoint();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_TurnToWaypoint_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBTTask_TurnToWaypoint ***************************************************
void UBTTask_TurnToWaypoint::StaticRegisterNativesUBTTask_TurnToWaypoint()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBTTask_TurnToWaypoint;
UClass* UBTTask_TurnToWaypoint::GetPrivateStaticClass()
{
	using TClass = UBTTask_TurnToWaypoint;
	if (!Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BTTask_TurnToWaypoint"),
			Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.InnerSingleton,
			StaticRegisterNativesUBTTask_TurnToWaypoint,
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
	return Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.InnerSingleton;
}
UClass* Z_Construct_UClass_UBTTask_TurnToWaypoint_NoRegister()
{
	return UBTTask_TurnToWaypoint::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Task/BTTask_TurnToWaypoint.h" },
		{ "ModuleRelativePath", "Public/Task/BTTask_TurnToWaypoint.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinTurnAngle_MetaData[] = {
		{ "Category", "Turn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb0\x8f\xe4\xba\x8e\xe8\xaf\xa5\xe8\xa7\x92\xe5\xba\xa6\xe5\xb0\xb1\xe4\xb8\x8d\xe5\x81\x9a\xe9\xa2\x84\xe8\xbd\xac\xe8\xba\xab\xef\xbc\x8c\xe7\x9b\xb4\xe6\x8e\xa5\xe6\x88\x90\xe5\x8a\x9f\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_TurnToWaypoint.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb0\x8f\xe4\xba\x8e\xe8\xaf\xa5\xe8\xa7\x92\xe5\xba\xa6\xe5\xb0\xb1\xe4\xb8\x8d\xe5\x81\x9a\xe9\xa2\x84\xe8\xbd\xac\xe8\xba\xab\xef\xbc\x8c\xe7\x9b\xb4\xe6\x8e\xa5\xe6\x88\x90\xe5\x8a\x9f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnSpeed_MetaData[] = {
		{ "Category", "Turn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8e\x9f\xe5\x9c\xb0\xe8\xbd\xac\xe5\x90\x91\xe9\x80\x9f\xe5\xba\xa6\xef\xbc\x88\xe5\xba\xa6/\xe7\xa7\x92\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_TurnToWaypoint.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8e\x9f\xe5\x9c\xb0\xe8\xbd\xac\xe5\x90\x91\xe9\x80\x9f\xe5\xba\xa6\xef\xbc\x88\xe5\xba\xa6/\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AcceptYawError_MetaData[] = {
		{ "Category", "Turn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xaf\xaf\xe5\xb7\xae\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_TurnToWaypoint.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xaf\xaf\xe5\xb7\xae\xe9\x98\x88\xe5\x80\xbc\xef\xbc\x88\xe5\xba\xa6\xef\xbc\x89" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinTurnAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TurnSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AcceptYawError;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_TurnToWaypoint>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_MinTurnAngle = { "MinTurnAngle", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_TurnToWaypoint, MinTurnAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinTurnAngle_MetaData), NewProp_MinTurnAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_TurnSpeed = { "TurnSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_TurnToWaypoint, TurnSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnSpeed_MetaData), NewProp_TurnSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_AcceptYawError = { "AcceptYawError", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_TurnToWaypoint, AcceptYawError), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AcceptYawError_MetaData), NewProp_AcceptYawError_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_MinTurnAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_TurnSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::NewProp_AcceptYawError,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::ClassParams = {
	&UBTTask_TurnToWaypoint::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBTTask_TurnToWaypoint()
{
	if (!Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.OuterSingleton, Z_Construct_UClass_UBTTask_TurnToWaypoint_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBTTask_TurnToWaypoint.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_TurnToWaypoint);
UBTTask_TurnToWaypoint::~UBTTask_TurnToWaypoint() {}
// ********** End Class UBTTask_TurnToWaypoint *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_TurnToWaypoint_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_TurnToWaypoint, UBTTask_TurnToWaypoint::StaticClass, TEXT("UBTTask_TurnToWaypoint"), &Z_Registration_Info_UClass_UBTTask_TurnToWaypoint, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_TurnToWaypoint), 1943519501U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_TurnToWaypoint_h__Script_Invisible_2103407539(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_TurnToWaypoint_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_TurnToWaypoint_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
