// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InvisibleHUD.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInvisibleHUD() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AHUD();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleHUD();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleHUD_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInvisibleHUD ************************************************************
void AInvisibleHUD::StaticRegisterNativesAInvisibleHUD()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInvisibleHUD;
UClass* AInvisibleHUD::GetPrivateStaticClass()
{
	using TClass = AInvisibleHUD;
	if (!Z_Registration_Info_UClass_AInvisibleHUD.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InvisibleHUD"),
			Z_Registration_Info_UClass_AInvisibleHUD.InnerSingleton,
			StaticRegisterNativesAInvisibleHUD,
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
	return Z_Registration_Info_UClass_AInvisibleHUD.InnerSingleton;
}
UClass* Z_Construct_UClass_AInvisibleHUD_NoRegister()
{
	return AInvisibleHUD::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInvisibleHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "InvisibleHUD.h" },
		{ "ModuleRelativePath", "Public/InvisibleHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInvisibleHUD>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AInvisibleHUD_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AHUD,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleHUD_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInvisibleHUD_Statics::ClassParams = {
	&AInvisibleHUD::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleHUD_Statics::Class_MetaDataParams), Z_Construct_UClass_AInvisibleHUD_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInvisibleHUD()
{
	if (!Z_Registration_Info_UClass_AInvisibleHUD.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInvisibleHUD.OuterSingleton, Z_Construct_UClass_AInvisibleHUD_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInvisibleHUD.OuterSingleton;
}
AInvisibleHUD::AInvisibleHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInvisibleHUD);
AInvisibleHUD::~AInvisibleHUD() {}
// ********** End Class AInvisibleHUD **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleHUD_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInvisibleHUD, AInvisibleHUD::StaticClass, TEXT("AInvisibleHUD"), &Z_Registration_Info_UClass_AInvisibleHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInvisibleHUD), 1692375498U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleHUD_h__Script_Invisible_1116417822(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleHUD_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleHUD_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
