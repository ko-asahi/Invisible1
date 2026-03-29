// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/Enum/WaypointTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeWaypointTypes() {}

// ********** Begin Cross Module References ********************************************************
INVISIBLE_API UEnum* Z_Construct_UEnum_Invisible_EWaypointBehavior();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EWaypointBehavior *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EWaypointBehavior;
static UEnum* EWaypointBehavior_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EWaypointBehavior.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EWaypointBehavior.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Invisible_EWaypointBehavior, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("EWaypointBehavior"));
	}
	return Z_Registration_Info_UEnum_EWaypointBehavior.OuterSingleton;
}
template<> INVISIBLE_API UEnum* StaticEnum<EWaypointBehavior>()
{
	return EWaypointBehavior_StaticEnum();
}
struct Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe8\xa1\x8c\xe4\xb8\xba\xe7\xb1\xbb\xe5\x9e\x8b\n" },
#endif
		{ "LookAround.DisplayName", "\xe5\x81\x9c\xe4\xb8\x8b\xe6\x89\xab\xe8\xa7\x86" },
		{ "LookAround.Name", "EWaypointBehavior::LookAround" },
		{ "ModuleRelativePath", "Public/Enemy/Enum/WaypointTypes.h" },
		{ "None.DisplayName", "\xe7\x9b\xb4\xe6\x8e\xa5\xe7\xbb\x8f\xe8\xbf\x87" },
		{ "None.Name", "EWaypointBehavior::None" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xa1\xe9\x80\xbb\xe7\x82\xb9\xe8\xa1\x8c\xe4\xb8\xba\xe7\xb1\xbb\xe5\x9e\x8b" },
#endif
		{ "Wait.DisplayName", "\xe5\x8e\x9f\xe5\x9c\xb0\xe7\xad\x89\xe5\xbe\x85" },
		{ "Wait.Name", "EWaypointBehavior::Wait" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EWaypointBehavior::None", (int64)EWaypointBehavior::None },
		{ "EWaypointBehavior::LookAround", (int64)EWaypointBehavior::LookAround },
		{ "EWaypointBehavior::Wait", (int64)EWaypointBehavior::Wait },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	"EWaypointBehavior",
	"EWaypointBehavior",
	Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Invisible_EWaypointBehavior()
{
	if (!Z_Registration_Info_UEnum_EWaypointBehavior.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EWaypointBehavior.InnerSingleton, Z_Construct_UEnum_Invisible_EWaypointBehavior_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EWaypointBehavior.InnerSingleton;
}
// ********** End Enum EWaypointBehavior ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_Enum_WaypointTypes_h__Script_Invisible_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EWaypointBehavior_StaticEnum, TEXT("EWaypointBehavior"), &Z_Registration_Info_UEnum_EWaypointBehavior, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3700645603U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_Enum_WaypointTypes_h__Script_Invisible_3573131407(TEXT("/Script/Invisible"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_Enum_WaypointTypes_h__Script_Invisible_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_Enum_WaypointTypes_h__Script_Invisible_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
