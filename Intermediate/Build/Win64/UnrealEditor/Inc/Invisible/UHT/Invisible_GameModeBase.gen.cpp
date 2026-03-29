// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Invisible_GameModeBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInvisible_GameModeBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisible_GameModeBase();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisible_GameModeBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInvisible_GameModeBase **************************************************
void AInvisible_GameModeBase::StaticRegisterNativesAInvisible_GameModeBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInvisible_GameModeBase;
UClass* AInvisible_GameModeBase::GetPrivateStaticClass()
{
	using TClass = AInvisible_GameModeBase;
	if (!Z_Registration_Info_UClass_AInvisible_GameModeBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("Invisible_GameModeBase"),
			Z_Registration_Info_UClass_AInvisible_GameModeBase.InnerSingleton,
			StaticRegisterNativesAInvisible_GameModeBase,
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
	return Z_Registration_Info_UClass_AInvisible_GameModeBase.InnerSingleton;
}
UClass* Z_Construct_UClass_AInvisible_GameModeBase_NoRegister()
{
	return AInvisible_GameModeBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInvisible_GameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Invisible_GameModeBase.h" },
		{ "ModuleRelativePath", "Public/Invisible_GameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInvisible_GameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AInvisible_GameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisible_GameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInvisible_GameModeBase_Statics::ClassParams = {
	&AInvisible_GameModeBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisible_GameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AInvisible_GameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInvisible_GameModeBase()
{
	if (!Z_Registration_Info_UClass_AInvisible_GameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInvisible_GameModeBase.OuterSingleton, Z_Construct_UClass_AInvisible_GameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInvisible_GameModeBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInvisible_GameModeBase);
AInvisible_GameModeBase::~AInvisible_GameModeBase() {}
// ********** End Class AInvisible_GameModeBase ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInvisible_GameModeBase, AInvisible_GameModeBase::StaticClass, TEXT("AInvisible_GameModeBase"), &Z_Registration_Info_UClass_AInvisible_GameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInvisible_GameModeBase), 4040536419U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h__Script_Invisible_2201498447(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
