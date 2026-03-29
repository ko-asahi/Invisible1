// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InvisiblePlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInvisiblePlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_AEditModeCamera_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerController();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerController_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_UAIInfoPanelWidget_NoRegister();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FLockedAIPath();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FLockedAIPath *****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLockedAIPath;
class UScriptStruct* FLockedAIPath::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLockedAIPath.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLockedAIPath.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLockedAIPath, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("LockedAIPath"));
	}
	return Z_Registration_Info_UScriptStruct_FLockedAIPath.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FLockedAIPath_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */// \xe4\xbf\x9d\xe5\xad\x98\xe5\x8d\x95\xe4\xb8\xaa""ai\xe8\xb7\xaf\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "// \xe4\xbf\x9d\xe5\xad\x98\xe5\x8d\x95\xe4\xb8\xaa""ai\xe8\xb7\xaf\xe5\xbe\x84" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLockedAIPath>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLockedAIPath_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"LockedAIPath",
	nullptr,
	0,
	sizeof(FLockedAIPath),
	alignof(FLockedAIPath),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLockedAIPath_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLockedAIPath_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLockedAIPath()
{
	if (!Z_Registration_Info_UScriptStruct_FLockedAIPath.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLockedAIPath.InnerSingleton, Z_Construct_UScriptStruct_FLockedAIPath_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FLockedAIPath.InnerSingleton;
}
// ********** End ScriptStruct FLockedAIPath *******************************************************

// ********** Begin Class AInvisiblePlayerController ***********************************************
void AInvisiblePlayerController::StaticRegisterNativesAInvisiblePlayerController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInvisiblePlayerController;
UClass* AInvisiblePlayerController::GetPrivateStaticClass()
{
	using TClass = AInvisiblePlayerController;
	if (!Z_Registration_Info_UClass_AInvisiblePlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InvisiblePlayerController"),
			Z_Registration_Info_UClass_AInvisiblePlayerController.InnerSingleton,
			StaticRegisterNativesAInvisiblePlayerController,
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
	return Z_Registration_Info_UClass_AInvisiblePlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_AInvisiblePlayerController_NoRegister()
{
	return AInvisiblePlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInvisiblePlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "InvisiblePlayerController.h" },
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb7\x9f\xe9\x9a\x8f\xe6\xa8\xa1\xe5\xbc\x8f\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb7\x9f\xe9\x9a\x8f\xe6\xa8\xa1\xe5\xbc\x8f\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditModeMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SwitchModeMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x88\x87\xe6\x8d\xa2\xe5\x8a\x9f\xe8\x83\xbd\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\x87\xe6\x8d\xa2\xe5\x8a\x9f\xe8\x83\xbd\xe5\xa2\x9e\xe5\xbc\xba\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SwitchModeAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x88\x87\xe6\x8d\xa2\xe8\xbe\x93\xe5\x85\xa5\xe6\xa8\xa1\xe5\xbc\x8f\xe6\x8c\x89\xe9\x94\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\x87\xe6\x8d\xa2\xe8\xbe\x93\xe5\x85\xa5\xe6\xa8\xa1\xe5\xbc\x8f\xe6\x8c\x89\xe9\x94\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsEditMode_MetaData[] = {
		{ "Category", "Input|IsEditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x88\xa4\xe5\xae\x9a\xe5\x8f\x82\xe6\x95\xb0(\xe9\xa2\x84\xe7\x95\x99\xef\xbc\x8c\xe5\x8f\xaf\xe7\x94\xa8\xe4\xba\x8e\xe5\x88\x87\xe6\x8d\xa2\xe6\x97\xb6\xe7\x9a\x84\xe5\x8a\xa8\xe7\x94\xbb\xe6\x95\x88\xe6\x9e\x9c)\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x88\xa4\xe5\xae\x9a\xe5\x8f\x82\xe6\x95\xb0(\xe9\xa2\x84\xe7\x95\x99\xef\xbc\x8c\xe5\x8f\xaf\xe7\x94\xa8\xe4\xba\x8e\xe5\x88\x87\xe6\x8d\xa2\xe6\x97\xb6\xe7\x9a\x84\xe5\x8a\xa8\xe7\x94\xbb\xe6\x95\x88\xe6\x9e\x9c)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// =====\xe8\xb7\x9f\xe9\x9a\x8f\xe6\xa8\xa1\xe5\xbc\x8f\xe8\xbe\x93\xe5\x85\xa5=====\n// \xe7\xa7\xbb\xe5\x8a\xa8\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=====\xe8\xb7\x9f\xe9\x9a\x8f\xe6\xa8\xa1\xe5\xbc\x8f\xe8\xbe\x93\xe5\x85\xa5=====\n\xe7\xa7\xbb\xe5\x8a\xa8\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotateAction_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x97\x8b\xe8\xbd\xac\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\x8b\xe8\xbd\xac\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotateHoldAction_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x97\x8b\xe8\xbd\xac\xe7\x8a\xb6\xe6\x80\x81\xe6\x8c\x89\xe9\x94\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\x8b\xe8\xbd\xac\xe7\x8a\xb6\xe6\x80\x81\xe6\x8c\x89\xe9\x94\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrouchAction_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb9\xb2\xe4\xb8\x8b\xe8\xbe\x93\xe5\x85\xa5\xe6\x8c\x89\xe9\x94\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb9\xb2\xe4\xb8\x8b\xe8\xbe\x93\xe5\x85\xa5\xe6\x8c\x89\xe9\x94\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RunAction_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa5\x94\xe8\xb7\x91\xe8\xbe\x93\xe5\x85\xa5\xe6\x8c\x89\xe9\x94\xae\xef\xbc\x88\xe6\x8c\x89\xe4\xbd\x8f\xe6\x97\xb6\xe8\xb7\x91\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa5\x94\xe8\xb7\x91\xe8\xbe\x93\xe5\x85\xa5\xe6\x8c\x89\xe9\x94\xae\xef\xbc\x88\xe6\x8c\x89\xe4\xbd\x8f\xe6\x97\xb6\xe8\xb7\x91\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsRunning_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe5\xa5\x94\xe8\xb7\x91\xe7\x8a\xb6\xe6\x80\x81\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe5\xa5\x94\xe8\xb7\x91\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OrbitYawSpeed_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x97\x8b\xe8\xbd\xac\xe7\x81\xb5\xe6\x95\x8f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\x8b\xe8\xbd\xac\xe7\x81\xb5\xe6\x95\x8f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterRotateSpeed_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa7\x92\xe8\x89\xb2\xe8\xbd\xac\xe5\x90\x91\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x92\xe8\x89\xb2\xe8\xbd\xac\xe5\x90\x91\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRotateHeld_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x95\x9c\xe5\xa4\xb4\xe6\x97\x8b\xe8\xbd\xac\xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe5\x8a\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x95\x9c\xe5\xa4\xb4\xe6\x97\x8b\xe8\xbd\xac\xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe5\x8a\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsCrouching_MetaData[] = {
		{ "Category", "Input|FollowMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe8\xb9\xb2\xe4\xb8\x8b\xe7\x8a\xb6\xe6\x80\x81\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe8\xb9\xb2\xe4\xb8\x8b\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditPanAction_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xa7\xbb\xe5\x8a\xa8\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xa7\xbb\xe5\x8a\xa8\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditRotateAction_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x97\x8b\xe8\xbd\xac\xe8\xbe\x93\xe5\x85\xa5\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\x8b\xe8\xbd\xac\xe8\xbe\x93\xe5\x85\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditRotateHoldAction_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x97\x8b\xe8\xbd\xac\xe7\x8a\xb6\xe6\x80\x81\xe6\x8c\x89\xe9\x94\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x97\x8b\xe8\xbd\xac\xe7\x8a\xb6\xe6\x80\x81\xe6\x8c\x89\xe9\x94\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditSelectAction_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8d\x95\xe4\xbd\x8d\xe9\x80\x89\xe6\x8b\xa9\xe6\x8c\x89\xe9\x94\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8d\x95\xe4\xbd\x8d\xe9\x80\x89\xe6\x8b\xa9\xe6\x8c\x89\xe9\x94\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditModeCameraTransitionSpeed_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe8\xbf\x87\xe6\xb8\xa1\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe8\xbf\x87\xe6\xb8\xa1\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectedActor_MetaData[] = {
		{ "Category", "EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe9\x80\x89\xe6\x8b\xa9""Actor\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe9\x80\x89\xe6\x8b\xa9""Actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayPathEnergy_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UI\xe6\x98\xbe\xe7\xa4\xba\xe7\x94\xa8\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x88\xe6\x8b\x96\xe6\x8b\xbd\xe4\xb8\xad\xe5\xae\x9e\xe6\x97\xb6\xe5\x8f\x98\xe5\x8c\x96\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UI\xe6\x98\xbe\xe7\xa4\xba\xe7\x94\xa8\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x88\xe6\x8b\x96\xe6\x8b\xbd\xe4\xb8\xad\xe5\xae\x9e\xe6\x97\xb6\xe5\x8f\x98\xe5\x8c\x96\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinPathDistance_MetaData[] = {
		{ "Category", "EditMode|Path" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe4\xbd\x8e\xe4\xba\x8e\xe8\xaf\xa5\xe5\x80\xbc\xe6\x97\xb6\xef\xbc\x8c\xe4\xb8\x8d\xe7\xbb\x98\xe5\x88\xb6\xe8\xb7\xaf\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbd\x8e\xe4\xba\x8e\xe8\xaf\xa5\xe5\x80\xbc\xe6\x97\xb6\xef\xbc\x8c\xe4\xb8\x8d\xe7\xbb\x98\xe5\x88\xb6\xe8\xb7\xaf\xe5\xbe\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PathDebugZOffset_MetaData[] = {
		{ "Category", "EditMode|Path" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xbb\x98\xe5\x88\xb6\xe9\xab\x98\xe5\xba\xa6\xe5\x8f\x82\xe6\x95\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbb\x98\xe5\x88\xb6\xe9\xab\x98\xe5\xba\xa6\xe5\x8f\x82\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditRemovePathAction_MetaData[] = {
		{ "Category", "Input|EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x88\xa0\xe9\x99\xa4\xe5\xb7\xb2\xe9\x94\x81\xe5\xae\x9a\xe8\xb7\xaf\xe5\xbe\x84\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\xa0\xe9\x99\xa4\xe5\xb7\xb2\xe9\x94\x81\xe5\xae\x9a\xe8\xb7\xaf\xe5\xbe\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PathDragPixelThreshold_MetaData[] = {
		{ "Category", "EditMode|Path" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe9\xbc\xa0\xe6\xa0\x87\xe4\xbd\x8d\xe7\xa7\xbb\xe8\xb6\x85\xe8\xbf\x87\xe8\xaf\xa5\xe9\x98\x88\xe5\x80\xbc\xe6\x97\xb6\xef\xbc\x8c\xe8\xa7\x86\xe4\xb8\xba\xe6\x8b\x96\xe6\x8b\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe9\xbc\xa0\xe6\xa0\x87\xe4\xbd\x8d\xe7\xa7\xbb\xe8\xb6\x85\xe8\xbf\x87\xe8\xaf\xa5\xe9\x98\x88\xe5\x80\xbc\xe6\x97\xb6\xef\xbc\x8c\xe8\xa7\x86\xe4\xb8\xba\xe6\x8b\x96\xe6\x8b\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPathEnergy_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x9c\x80\xe5\xa4\xa7\xe8\x83\xbd\xe9\x87\x8f\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\x80\xe5\xa4\xa7\xe8\x83\xbd\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPathEnergy_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe8\x83\xbd\xe9\x87\x8f\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe8\x83\xbd\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PathEnergyCostPerUnit_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\xaf\x8f\xe5\x8d\x95\xe4\xbd\x8d\xe7\x9a\x84\xe8\x83\xbd\xe9\x87\x8f\xe6\xb6\x88\xe8\x80\x97\xef\xbc\x88\xe9\xbb\x98\xe8\xae\xa4 1\xe7\xb1\xb3 = 1\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe5\x8d\x95\xe4\xbd\x8d\xe7\x9a\x84\xe8\x83\xbd\xe9\x87\x8f\xe6\xb6\x88\xe8\x80\x97\xef\xbc\x88\xe9\xbb\x98\xe8\xae\xa4 1\xe7\xb1\xb3 = 1\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnergyRegenDelay_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x80\x80\xe5\x87\xba\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x90\x8e\xe5\xbc\x80\xe5\xa7\x8b\xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x80\x80\xe5\x87\xba\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe5\x90\x8e\xe5\xbc\x80\xe5\xa7\x8b\xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnergyRegenRate_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f\xe9\x80\x9f\xe7\x8e\x87\xef\xbc\x88\xe6\xaf\x8f\xe7\xa7\x92\xe5\x9b\x9e\xe5\xa4\x8d\xe7\x9a\x84\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f\xe9\x80\x9f\xe7\x8e\x87\xef\xbc\x88\xe6\xaf\x8f\xe7\xa7\x92\xe5\x9b\x9e\xe5\xa4\x8d\xe7\x9a\x84\xe8\x83\xbd\xe9\x87\x8f\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsRegenEnergy_MetaData[] = {
		{ "Category", "EditMode|Energy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xaf\xe5\x90\xa6\xe6\xad\xa3\xe5\x9c\xa8\xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe6\xad\xa3\xe5\x9c\xa8\xe5\x9b\x9e\xe5\xa4\x8d\xe8\x83\xbd\xe9\x87\x8f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIInfoPanelClass_MetaData[] = {
		{ "Category", "EditMode|AIInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ai\xe5\x8d\x95\xe4\xbd\x8d\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xbaUI\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ai\xe5\x8d\x95\xe4\xbd\x8d\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xbaUI" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIInfoPanelInstance_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ai\xe5\x8d\x95\xe4\xbd\x8d\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xba\xe5\xae\x9e\xe4\xbe\x8b\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ai\xe5\x8d\x95\xe4\xbd\x8d\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xba\xe5\xae\x9e\xe4\xbe\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditModeCameraClass_MetaData[] = {
		{ "Category", "EditMode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8f\xaf\xe5\x9c\xa8\xe8\x93\x9d\xe5\x9b\xbe\xe4\xb8\xad\xe6\x8c\x87\xe5\xae\x9a\xe5\x85\xb7\xe4\xbd\x93\xe7\x9a\x84 EditModeCamera \xe8\x93\x9d\xe5\x9b\xbe\xe7\xb1\xbb\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8f\xaf\xe5\x9c\xa8\xe8\x93\x9d\xe5\x9b\xbe\xe4\xb8\xad\xe6\x8c\x87\xe5\xae\x9a\xe5\x85\xb7\xe4\xbd\x93\xe7\x9a\x84 EditModeCamera \xe8\x93\x9d\xe5\x9b\xbe\xe7\xb1\xbb" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EditCamera_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x94\x9f\xe6\x88\x90\xe7\x9b\xb8\xe6\x9c\xba\xe5\xae\x9e\xe4\xbe\x8b(\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6)\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisiblePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\x9f\xe6\x88\x90\xe7\x9b\xb8\xe6\x9c\xba\xe5\xae\x9e\xe4\xbe\x8b(\xe8\xbf\x90\xe8\xa1\x8c\xe6\x97\xb6)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditModeMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SwitchModeMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SwitchModeAction;
	static void NewProp_bIsEditMode_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsEditMode;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RotateAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RotateHoldAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CrouchAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RunAction;
	static void NewProp_bIsRunning_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRunning;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OrbitYawSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CharacterRotateSpeed;
	static void NewProp_bRotateHeld_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRotateHeld;
	static void NewProp_bIsCrouching_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsCrouching;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditPanAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditRotateAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditRotateHoldAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditSelectAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EditModeCameraTransitionSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectedActor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DisplayPathEnergy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinPathDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PathDebugZOffset;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditRemovePathAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PathDragPixelThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxPathEnergy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentPathEnergy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PathEnergyCostPerUnit;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EnergyRegenDelay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EnergyRegenRate;
	static void NewProp_bIsRegenEnergy_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRegenEnergy;
	static const UECodeGen_Private::FClassPropertyParams NewProp_AIInfoPanelClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AIInfoPanelInstance;
	static const UECodeGen_Private::FClassPropertyParams NewProp_EditModeCameraClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EditCamera;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInvisiblePlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_FollowMappingContext = { "FollowMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, FollowMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowMappingContext_MetaData), NewProp_FollowMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeMappingContext = { "EditModeMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditModeMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditModeMappingContext_MetaData), NewProp_EditModeMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SwitchModeMappingContext = { "SwitchModeMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, SwitchModeMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SwitchModeMappingContext_MetaData), NewProp_SwitchModeMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SwitchModeAction = { "SwitchModeAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, SwitchModeAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SwitchModeAction_MetaData), NewProp_SwitchModeAction_MetaData) };
void Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsEditMode_SetBit(void* Obj)
{
	((AInvisiblePlayerController*)Obj)->bIsEditMode = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsEditMode = { "bIsEditMode", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInvisiblePlayerController), &Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsEditMode_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsEditMode_MetaData), NewProp_bIsEditMode_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RotateAction = { "RotateAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, RotateAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotateAction_MetaData), NewProp_RotateAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RotateHoldAction = { "RotateHoldAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, RotateHoldAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotateHoldAction_MetaData), NewProp_RotateHoldAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CrouchAction = { "CrouchAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, CrouchAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrouchAction_MetaData), NewProp_CrouchAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RunAction = { "RunAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, RunAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RunAction_MetaData), NewProp_RunAction_MetaData) };
void Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRunning_SetBit(void* Obj)
{
	((AInvisiblePlayerController*)Obj)->bIsRunning = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRunning = { "bIsRunning", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInvisiblePlayerController), &Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRunning_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsRunning_MetaData), NewProp_bIsRunning_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_OrbitYawSpeed = { "OrbitYawSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, OrbitYawSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OrbitYawSpeed_MetaData), NewProp_OrbitYawSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CharacterRotateSpeed = { "CharacterRotateSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, CharacterRotateSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterRotateSpeed_MetaData), NewProp_CharacterRotateSpeed_MetaData) };
void Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bRotateHeld_SetBit(void* Obj)
{
	((AInvisiblePlayerController*)Obj)->bRotateHeld = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bRotateHeld = { "bRotateHeld", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInvisiblePlayerController), &Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bRotateHeld_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRotateHeld_MetaData), NewProp_bRotateHeld_MetaData) };
void Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsCrouching_SetBit(void* Obj)
{
	((AInvisiblePlayerController*)Obj)->bIsCrouching = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsCrouching = { "bIsCrouching", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInvisiblePlayerController), &Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsCrouching_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsCrouching_MetaData), NewProp_bIsCrouching_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditPanAction = { "EditPanAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditPanAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditPanAction_MetaData), NewProp_EditPanAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRotateAction = { "EditRotateAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditRotateAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditRotateAction_MetaData), NewProp_EditRotateAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRotateHoldAction = { "EditRotateHoldAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditRotateHoldAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditRotateHoldAction_MetaData), NewProp_EditRotateHoldAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditSelectAction = { "EditSelectAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditSelectAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditSelectAction_MetaData), NewProp_EditSelectAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeCameraTransitionSpeed = { "EditModeCameraTransitionSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditModeCameraTransitionSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditModeCameraTransitionSpeed_MetaData), NewProp_EditModeCameraTransitionSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SelectedActor = { "SelectedActor", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, SelectedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectedActor_MetaData), NewProp_SelectedActor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_DisplayPathEnergy = { "DisplayPathEnergy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, DisplayPathEnergy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayPathEnergy_MetaData), NewProp_DisplayPathEnergy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MinPathDistance = { "MinPathDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, MinPathDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinPathDistance_MetaData), NewProp_MinPathDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathDebugZOffset = { "PathDebugZOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, PathDebugZOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PathDebugZOffset_MetaData), NewProp_PathDebugZOffset_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRemovePathAction = { "EditRemovePathAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditRemovePathAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditRemovePathAction_MetaData), NewProp_EditRemovePathAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathDragPixelThreshold = { "PathDragPixelThreshold", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, PathDragPixelThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PathDragPixelThreshold_MetaData), NewProp_PathDragPixelThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MaxPathEnergy = { "MaxPathEnergy", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, MaxPathEnergy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPathEnergy_MetaData), NewProp_MaxPathEnergy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CurrentPathEnergy = { "CurrentPathEnergy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, CurrentPathEnergy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentPathEnergy_MetaData), NewProp_CurrentPathEnergy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathEnergyCostPerUnit = { "PathEnergyCostPerUnit", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, PathEnergyCostPerUnit), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PathEnergyCostPerUnit_MetaData), NewProp_PathEnergyCostPerUnit_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EnergyRegenDelay = { "EnergyRegenDelay", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EnergyRegenDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnergyRegenDelay_MetaData), NewProp_EnergyRegenDelay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EnergyRegenRate = { "EnergyRegenRate", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EnergyRegenRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnergyRegenRate_MetaData), NewProp_EnergyRegenRate_MetaData) };
void Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRegenEnergy_SetBit(void* Obj)
{
	((AInvisiblePlayerController*)Obj)->bIsRegenEnergy = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRegenEnergy = { "bIsRegenEnergy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInvisiblePlayerController), &Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRegenEnergy_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsRegenEnergy_MetaData), NewProp_bIsRegenEnergy_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_AIInfoPanelClass = { "AIInfoPanelClass", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, AIInfoPanelClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UAIInfoPanelWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIInfoPanelClass_MetaData), NewProp_AIInfoPanelClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_AIInfoPanelInstance = { "AIInfoPanelInstance", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, AIInfoPanelInstance), Z_Construct_UClass_UAIInfoPanelWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIInfoPanelInstance_MetaData), NewProp_AIInfoPanelInstance_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeCameraClass = { "EditModeCameraClass", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditModeCameraClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AEditModeCamera_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditModeCameraClass_MetaData), NewProp_EditModeCameraClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditCamera = { "EditCamera", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisiblePlayerController, EditCamera), Z_Construct_UClass_AEditModeCamera_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EditCamera_MetaData), NewProp_EditCamera_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInvisiblePlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_FollowMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SwitchModeMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SwitchModeAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsEditMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RotateAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RotateHoldAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CrouchAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_RunAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRunning,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_OrbitYawSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CharacterRotateSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bRotateHeld,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsCrouching,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditPanAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRotateAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRotateHoldAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditSelectAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeCameraTransitionSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_SelectedActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_DisplayPathEnergy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MinPathDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathDebugZOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditRemovePathAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathDragPixelThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_MaxPathEnergy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_CurrentPathEnergy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_PathEnergyCostPerUnit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EnergyRegenDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EnergyRegenRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_bIsRegenEnergy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_AIInfoPanelClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_AIInfoPanelInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditModeCameraClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisiblePlayerController_Statics::NewProp_EditCamera,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AInvisiblePlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInvisiblePlayerController_Statics::ClassParams = {
	&AInvisiblePlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AInvisiblePlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerController_Statics::PropPointers),
	0,
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisiblePlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AInvisiblePlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInvisiblePlayerController()
{
	if (!Z_Registration_Info_UClass_AInvisiblePlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInvisiblePlayerController.OuterSingleton, Z_Construct_UClass_AInvisiblePlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInvisiblePlayerController.OuterSingleton;
}
AInvisiblePlayerController::AInvisiblePlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInvisiblePlayerController);
AInvisiblePlayerController::~AInvisiblePlayerController() {}
// ********** End Class AInvisiblePlayerController *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FLockedAIPath::StaticStruct, Z_Construct_UScriptStruct_FLockedAIPath_Statics::NewStructOps, TEXT("LockedAIPath"), &Z_Registration_Info_UScriptStruct_FLockedAIPath, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLockedAIPath), 1064708489U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInvisiblePlayerController, AInvisiblePlayerController::StaticClass, TEXT("AInvisiblePlayerController"), &Z_Registration_Info_UClass_AInvisiblePlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInvisiblePlayerController), 255813405U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_193972901(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h__Script_Invisible_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
