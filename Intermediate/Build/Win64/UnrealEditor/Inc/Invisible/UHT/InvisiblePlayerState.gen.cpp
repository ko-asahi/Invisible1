// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InvisiblePlayerState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInvisiblePlayerState() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerState();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerState();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerState_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInvisiblePlayerState ****************************************************
void AInvisiblePlayerState::StaticRegisterNativesAInvisiblePlayerState()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInvisiblePlayerState;
UClass* AInvisiblePlayerState::GetPrivateStaticClass()
{
	using TClass = AInvisiblePlayerState;
	if (!Z_Registration_Info_UClass_AInvisiblePlayerState.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InvisiblePlayerState"),
			Z_Registration_Info_UClass_AInvisiblePlayerState.InnerSingleton,
			StaticRegisterNativesAInvisiblePlayerState,
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
	return Z_Registration_Info_UClass_AInvisiblePlayerState.InnerSingleton;
}
UClass* Z_Construct_UClass_AInvisiblePlayerState_NoRegister()
{
	return AInvisiblePlayerState::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInvisiblePlayerState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "InvisiblePlayerState.h" },
		{ "ModuleRelativePath", "Public/InvisiblePlayerState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInvisiblePlayerState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AInvisiblePlayerState_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerState,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerState_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInvisiblePlayerState_Statics::ClassParams = {
	&AInvisiblePlayerState::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerState_Statics::Class_MetaDataParams), Z_Construct_UClass_AInvisiblePlayerState_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInvisiblePlayerState()
{
	if (!Z_Registration_Info_UClass_AInvisiblePlayerState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInvisiblePlayerState.OuterSingleton, Z_Construct_UClass_AInvisiblePlayerState_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInvisiblePlayerState.OuterSingleton;
}
AInvisiblePlayerState::AInvisiblePlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInvisiblePlayerState);
AInvisiblePlayerState::~AInvisiblePlayerState() {}
// ********** End Class AInvisiblePlayerState ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInvisiblePlayerState, AInvisiblePlayerState::StaticClass, TEXT("AInvisiblePlayerState"), &Z_Registration_Info_UClass_AInvisiblePlayerState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInvisiblePlayerState), 3938353356U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h__Script_Invisible_2581993699(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
