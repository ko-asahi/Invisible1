// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Task/BTTask_StopMovement.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBTTask_StopMovement() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_StopMovement();
INVISIBLE_API UClass* Z_Construct_UClass_UBTTask_StopMovement_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBTTask_StopMovement *****************************************************
void UBTTask_StopMovement::StaticRegisterNativesUBTTask_StopMovement()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UBTTask_StopMovement;
UClass* UBTTask_StopMovement::GetPrivateStaticClass()
{
	using TClass = UBTTask_StopMovement;
	if (!Z_Registration_Info_UClass_UBTTask_StopMovement.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BTTask_StopMovement"),
			Z_Registration_Info_UClass_UBTTask_StopMovement.InnerSingleton,
			StaticRegisterNativesUBTTask_StopMovement,
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
	return Z_Registration_Info_UClass_UBTTask_StopMovement.InnerSingleton;
}
UClass* Z_Construct_UClass_UBTTask_StopMovement_NoRegister()
{
	return UBTTask_StopMovement::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBTTask_StopMovement_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe8\xa7\x92\xe8\x89\xb2\xe5\x81\x9c\xe6\xad\xa2\xe7\xa7\xbb\xe5\x8a\xa8\xe4\xba\x8b\xe4\xbb\xb6\n */" },
#endif
		{ "IncludePath", "Task/BTTask_StopMovement.h" },
		{ "ModuleRelativePath", "Public/Task/BTTask_StopMovement.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x92\xe8\x89\xb2\xe5\x81\x9c\xe6\xad\xa2\xe7\xa7\xbb\xe5\x8a\xa8\xe4\xba\x8b\xe4\xbb\xb6" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_StopMovement>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBTTask_StopMovement_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_StopMovement_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_StopMovement_Statics::ClassParams = {
	&UBTTask_StopMovement::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_StopMovement_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_StopMovement_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBTTask_StopMovement()
{
	if (!Z_Registration_Info_UClass_UBTTask_StopMovement.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_StopMovement.OuterSingleton, Z_Construct_UClass_UBTTask_StopMovement_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBTTask_StopMovement.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_StopMovement);
UBTTask_StopMovement::~UBTTask_StopMovement() {}
// ********** End Class UBTTask_StopMovement *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_StopMovement_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_StopMovement, UBTTask_StopMovement::StaticClass, TEXT("UBTTask_StopMovement"), &Z_Registration_Info_UClass_UBTTask_StopMovement, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_StopMovement), 584329132U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_StopMovement_h__Script_Invisible_3301897195(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_StopMovement_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Task_BTTask_StopMovement_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
