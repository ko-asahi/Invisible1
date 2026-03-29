// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Task/BTTask_Patrol.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBTTask_Patrol() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_Patrol();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_Patrol_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBTTask_Patrol ***********************************************************
void UBTTask_Patrol::StaticRegisterNativesUBTTask_Patrol()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBTTask_Patrol;
UClass* UBTTask_Patrol::GetPrivateStaticClass()
{
	using TClass = UBTTask_Patrol;
	if (!Z_Registration_Info_UClass_UBTTask_Patrol.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BTTask_Patrol"),
			Z_Registration_Info_UClass_UBTTask_Patrol.InnerSingleton,
			StaticRegisterNativesUBTTask_Patrol,
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
	return Z_Registration_Info_UClass_UBTTask_Patrol.InnerSingleton;
}
UClass* Z_Construct_UClass_UBTTask_Patrol_NoRegister()
{
	return UBTTask_Patrol::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBTTask_Patrol_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Task/BTTask_Patrol.h" },
		{ "ModuleRelativePath", "Public/Task/BTTask_Patrol.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AcceptanceRadius_MetaData[] = {
		{ "Category", "Patrol" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x88\xb0\xe8\xbe\xbe\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\x9a\x84\xe6\x8e\xa5\xe5\x8f\x97\xe5\x8d\x8a\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/Task/BTTask_Patrol.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\xb0\xe8\xbe\xbe\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe7\x9a\x84\xe6\x8e\xa5\xe5\x8f\x97\xe5\x8d\x8a\xe5\xbe\x84" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AcceptanceRadius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_Patrol>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBTTask_Patrol_Statics::NewProp_AcceptanceRadius = { "AcceptanceRadius", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_Patrol, AcceptanceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AcceptanceRadius_MetaData), NewProp_AcceptanceRadius_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTTask_Patrol_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_Patrol_Statics::NewProp_AcceptanceRadius,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_Patrol_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBTTask_Patrol_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_Patrol_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_Patrol_Statics::ClassParams = {
	&UBTTask_Patrol::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBTTask_Patrol_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_Patrol_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_Patrol_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_Patrol_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBTTask_Patrol()
{
	if (!Z_Registration_Info_UClass_UBTTask_Patrol.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_Patrol.OuterSingleton, Z_Construct_UClass_UBTTask_Patrol_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBTTask_Patrol.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_Patrol);
UBTTask_Patrol::~UBTTask_Patrol() {}
// ********** End Class UBTTask_Patrol *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_Patrol_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_Patrol, UBTTask_Patrol::StaticClass, TEXT("UBTTask_Patrol"), &Z_Registration_Info_UClass_UBTTask_Patrol, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_Patrol), 4133874392U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_Patrol_h__Script_Invisible_2996596101(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_Patrol_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_Patrol_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
