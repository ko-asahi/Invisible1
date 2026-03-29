// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/PlayerCharacter.h"
#include "GameplayTagContainer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePlayerCharacter() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UAIPerceptionStimuliSourceComponent_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDecalComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
GAMEPLAYTAGS_API UClass* Z_Construct_UClass_UGameplayTagAssetInterface_NoRegister();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTagContainer();
INVISIBLE_API UClass* Z_Construct_UClass_APlayerCharacter();
INVISIBLE_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FNoiseProfile();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FNoiseProfile *****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNoiseProfile;
class UScriptStruct* FNoiseProfile::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FNoiseProfile.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FNoiseProfile.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNoiseProfile, (UObject*)Z_Construct_UPackage__Script_Invisible(), TEXT("NoiseProfile"));
	}
	return Z_Registration_Info_UScriptStruct_FNoiseProfile.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FNoiseProfile_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe9\x85\x8d\xe7\xbd\xae\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe9\x85\x8d\xe7\xbd\xae\xe7\xbb\x93\xe6\x9e\x84\xe4\xbd\x93" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNoiseProfile>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNoiseProfile_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
	nullptr,
	&NewStructOps,
	"NoiseProfile",
	nullptr,
	0,
	sizeof(FNoiseProfile),
	alignof(FNoiseProfile),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNoiseProfile_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNoiseProfile_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNoiseProfile()
{
	if (!Z_Registration_Info_UScriptStruct_FNoiseProfile.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNoiseProfile.InnerSingleton, Z_Construct_UScriptStruct_FNoiseProfile_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FNoiseProfile.InnerSingleton;
}
// ********** End ScriptStruct FNoiseProfile *******************************************************

// ********** Begin Class APlayerCharacter Function HandleGlobalHearingRangeChanged ****************
struct Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics
{
	struct PlayerCharacter_eventHandleGlobalHearingRangeChanged_Parms
	{
		float NewRange;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\x91\xe5\x90\xac\xe5\x85\xa8\xe5\xb1\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe5\x8f\x98\xe5\x8c\x96\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\x91\xe5\x90\xac\xe5\x85\xa8\xe5\xb1\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe5\x8f\x98\xe5\x8c\x96" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::NewProp_NewRange = { "NewRange", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlayerCharacter_eventHandleGlobalHearingRangeChanged_Parms, NewRange), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::NewProp_NewRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlayerCharacter, nullptr, "HandleGlobalHearingRangeChanged", Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PlayerCharacter_eventHandleGlobalHearingRangeChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::PlayerCharacter_eventHandleGlobalHearingRangeChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlayerCharacter::execHandleGlobalHearingRangeChanged)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewRange);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleGlobalHearingRangeChanged(Z_Param_NewRange);
	P_NATIVE_END;
}
// ********** End Class APlayerCharacter Function HandleGlobalHearingRangeChanged ******************

// ********** Begin Class APlayerCharacter *********************************************************
void APlayerCharacter::StaticRegisterNativesAPlayerCharacter()
{
	UClass* Class = APlayerCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HandleGlobalHearingRangeChanged", &APlayerCharacter::execHandleGlobalHearingRangeChanged },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APlayerCharacter;
UClass* APlayerCharacter::GetPrivateStaticClass()
{
	using TClass = APlayerCharacter;
	if (!Z_Registration_Info_UClass_APlayerCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PlayerCharacter"),
			Z_Registration_Info_UClass_APlayerCharacter.InnerSingleton,
			StaticRegisterNativesAPlayerCharacter,
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
	return Z_Registration_Info_UClass_APlayerCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_APlayerCharacter_NoRegister()
{
	return APlayerCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APlayerCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/PlayerCharacter.h" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPivot_MetaData[] = {
		{ "Category", "PlayerCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ===== \xe7\x9b\xb8\xe6\x9c\xba\xe7\x9b\xb8\xe5\x85\xb3 =====\n// \xe5\xbc\xb9\xe7\xb0\xa7\xe8\x87\x82\xe6\x97\x8b\xe8\xbd\xac\xe5\x9c\x86\xe5\xbf\x83\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "===== \xe7\x9b\xb8\xe6\x9c\xba\xe7\x9b\xb8\xe5\x85\xb3 =====\n\xe5\xbc\xb9\xe7\xb0\xa7\xe8\x87\x82\xe6\x97\x8b\xe8\xbd\xac\xe5\x9c\x86\xe5\xbf\x83" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "Category", "PlayerCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe6\x97\x8b\xe8\xbd\xac\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88\xe5\xbc\xb9\xe7\xb0\xa7\xe8\x87\x82\xef\xbc\x89\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe6\x97\x8b\xe8\xbd\xac\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88\xe5\xbc\xb9\xe7\xb0\xa7\xe8\x87\x82\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "Category", "PlayerCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x8e\xa9\xe5\xae\xb6\xe8\xb7\x9f\xe9\x9a\x8f\xe6\x91\x84\xe5\x83\x8f\xe6\x9c\xba\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x8e\xa9\xe5\xae\xb6\xe8\xb7\x9f\xe9\x9a\x8f\xe6\x91\x84\xe5\x83\x8f\xe6\x9c\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrouchWalkSpeed_MetaData[] = {
		{ "Category", "Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb9\xb2\xe4\xb8\x8b\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb9\xb2\xe4\xb8\x8b\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NormalWalkSpeed_MetaData[] = {
		{ "Category", "Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\xad\xa3\xe5\xb8\xb8\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xad\xa3\xe5\xb8\xb8\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RunSpeed_MetaData[] = {
		{ "Category", "Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa5\x94\xe8\xb7\x91\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa5\x94\xe8\xb7\x91\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsRunning_MetaData[] = {
		{ "Category", "State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe5\xa5\x94\xe8\xb7\x91\xe7\x8a\xb6\xe6\x80\x81\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe5\xa4\x84\xe4\xba\x8e\xe5\xa5\x94\xe8\xb7\x91\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementStateTags_MetaData[] = {
		{ "Category", "State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xbd\x93\xe5\x89\x8d\xe7\xa7\xbb\xe5\x8a\xa8\xe7\x8a\xb6\xe6\x80\x81\xef\xbc\x88\xe5\x8d\x95Tag\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe7\xa7\xbb\xe5\x8a\xa8\xe7\x8a\xb6\xe6\x80\x81\xef\xbc\x88\xe5\x8d\x95Tag\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinMovementSpeed_MetaData[] = {
		{ "Category", "Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\xe5\x88\xa4\xe6\x96\xad\xe9\x98\x88\xe5\x80\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\xe5\x88\xa4\xe6\x96\xad\xe9\x98\x88\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkFootstepLoudness_MetaData[] = {
		{ "Category", "Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WalkFootstepFrequency_MetaData[] = {
		{ "Category", "Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RunFootstepLoudness_MetaData[] = {
		{ "Category", "AI|Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa5\x94\xe8\xb7\x91\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa5\x94\xe8\xb7\x91\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RunFootstepFrequency_MetaData[] = {
		{ "Category", "Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa5\x94\xe8\xb7\x91\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa5\x94\xe8\xb7\x91\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrouchFootstepLoudness_MetaData[] = {
		{ "Category", "AI|Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb9\xb2\xe4\xb8\x8b\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb9\xb2\xe4\xb8\x8b\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe5\x93\x8d\xe5\xba\xa6" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrouchFootstepFrequency_MetaData[] = {
		{ "Category", "Noise|Footstep" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xb9\xb2\xe4\xb8\x8b\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb9\xb2\xe4\xb8\x8b\xe8\xa1\x8c\xe8\xb5\xb0\xe8\x84\x9a\xe6\xad\xa5\xe9\xa2\x91\xe7\x8e\x87" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRingDecal_MetaData[] = {
		{ "Category", "Noise|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe8\xb4\xb4\xe8\x8a\xb1\xe7\xbb\x84\xe4\xbb\xb6  \n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe8\xb4\xb4\xe8\x8a\xb1\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRingMaterialBase_MetaData[] = {
		{ "Category", "Noise|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe5\x9f\xba\xe7\xa1\x80\xe6\x9d\x90\xe8\xb4\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe5\x9f\xba\xe7\xa1\x80\xe6\x9d\x90\xe8\xb4\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRingMID_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe5\x8a\xa8\xe6\x80\x81\xe6\x9d\x90\xe8\xb4\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe5\x8a\xa8\xe6\x80\x81\xe6\x9d\x90\xe8\xb4\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRingDuration_MetaData[] = {
		{ "Category", "Noise|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x97\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe6\x8c\x81\xe7\xbb\xad\xe6\x97\xb6\xe9\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseRingProjectionDepth_MetaData[] = {
		{ "Category", "Noise|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe6\x8a\x95\xe5\xb0\x84\xe6\xb7\xb1\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x99\xaa\xe5\xa3\xb0\xe5\x9c\x88\xe6\x8a\x95\xe5\xb0\x84\xe6\xb7\xb1\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayAreaMinWS_MetaData[] = {
		{ "Category", "Noise|Mask" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x85\xb3\xe5\x8d\xa1\xe6\x9c\x80\xe5\xb0\x8f\xe5\x9d\x90\xe6\xa0\x87\xef\xbc\x88\xe9\x81\xae\xe7\xbd\xa9\xe5\xb1\x82\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb3\xe5\x8d\xa1\xe6\x9c\x80\xe5\xb0\x8f\xe5\x9d\x90\xe6\xa0\x87\xef\xbc\x88\xe9\x81\xae\xe7\xbd\xa9\xe5\xb1\x82\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayAreaSizeWS_MetaData[] = {
		{ "Category", "Noise|Mask" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x85\xb3\xe5\x8d\xa1\xe6\x9c\x80\xe5\xa4\xa7\xe5\x9d\x90\xe6\xa0\x87\xef\xbc\x88\xe9\x81\xae\xe7\xbd\xa9\xe5\xb1\x82\xef\xbc\x89\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb3\xe5\x8d\xa1\xe6\x9c\x80\xe5\xa4\xa7\xe5\x9d\x90\xe6\xa0\x87\xef\xbc\x88\xe9\x81\xae\xe7\xbd\xa9\xe5\xb1\x82\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingStimuliSourceComp_MetaData[] = {
		{ "Category", "AI|Perception" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x98\xbe\xe5\xbc\x8f\xe6\xb3\xa8\xe5\x86\x8c\xe4\xb8\xba\xe5\x90\xac\xe8\xa7\x89\xe5\x88\xba\xe6\xbf\x80\xe6\xba\x90\xef\xbc\x8c\xe9\x81\xbf\xe5\x85\x8d\xe4\xb8\x8d\xe5\x90\x8c\xe7\x89\x88\xe6\x9c\xac\xe4\xb8\x8b\xe5\x99\xaa\xe5\xa3\xb0\xe4\xba\x8b\xe4\xbb\xb6\xe6\x97\xa0\xe6\xb3\x95\xe8\xa2\xab\xe6\x84\x9f\xe7\x9f\xa5\xe7\xb3\xbb\xe7\xbb\x9f\xe5\x85\xb3\xe8\x81\x94\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PlayerCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xbe\xe5\xbc\x8f\xe6\xb3\xa8\xe5\x86\x8c\xe4\xb8\xba\xe5\x90\xac\xe8\xa7\x89\xe5\x88\xba\xe6\xbf\x80\xe6\xba\x90\xef\xbc\x8c\xe9\x81\xbf\xe5\x85\x8d\xe4\xb8\x8d\xe5\x90\x8c\xe7\x89\x88\xe6\x9c\xac\xe4\xb8\x8b\xe5\x99\xaa\xe5\xa3\xb0\xe4\xba\x8b\xe4\xbb\xb6\xe6\x97\xa0\xe6\xb3\x95\xe8\xa2\xab\xe6\x84\x9f\xe7\x9f\xa5\xe7\xb3\xbb\xe7\xbb\x9f\xe5\x85\xb3\xe8\x81\x94" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraPivot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CrouchWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NormalWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RunSpeed;
	static void NewProp_bIsRunning_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRunning;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MovementStateTags;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinMovementSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WalkFootstepLoudness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WalkFootstepFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RunFootstepLoudness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RunFootstepFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CrouchFootstepLoudness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CrouchFootstepFrequency;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NoiseRingDecal;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NoiseRingMaterialBase;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NoiseRingMID;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseRingDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseRingProjectionDepth;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlayAreaMinWS;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlayAreaSizeWS;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HearingStimuliSourceComp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APlayerCharacter_HandleGlobalHearingRangeChanged, "HandleGlobalHearingRangeChanged" }, // 413888831
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayerCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CameraPivot = { "CameraPivot", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, CameraPivot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPivot_MetaData), NewProp_CameraPivot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchWalkSpeed = { "CrouchWalkSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, CrouchWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrouchWalkSpeed_MetaData), NewProp_CrouchWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NormalWalkSpeed = { "NormalWalkSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NormalWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NormalWalkSpeed_MetaData), NewProp_NormalWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunSpeed = { "RunSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, RunSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RunSpeed_MetaData), NewProp_RunSpeed_MetaData) };
void Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_SetBit(void* Obj)
{
	((APlayerCharacter*)Obj)->bIsRunning = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning = { "bIsRunning", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APlayerCharacter), &Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsRunning_MetaData), NewProp_bIsRunning_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_MovementStateTags = { "MovementStateTags", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, MovementStateTags), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementStateTags_MetaData), NewProp_MovementStateTags_MetaData) }; // 2104890724
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_MinMovementSpeed = { "MinMovementSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, MinMovementSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinMovementSpeed_MetaData), NewProp_MinMovementSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_WalkFootstepLoudness = { "WalkFootstepLoudness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, WalkFootstepLoudness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkFootstepLoudness_MetaData), NewProp_WalkFootstepLoudness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_WalkFootstepFrequency = { "WalkFootstepFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, WalkFootstepFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WalkFootstepFrequency_MetaData), NewProp_WalkFootstepFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunFootstepLoudness = { "RunFootstepLoudness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, RunFootstepLoudness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RunFootstepLoudness_MetaData), NewProp_RunFootstepLoudness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunFootstepFrequency = { "RunFootstepFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, RunFootstepFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RunFootstepFrequency_MetaData), NewProp_RunFootstepFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchFootstepLoudness = { "CrouchFootstepLoudness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, CrouchFootstepLoudness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrouchFootstepLoudness_MetaData), NewProp_CrouchFootstepLoudness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchFootstepFrequency = { "CrouchFootstepFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, CrouchFootstepFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrouchFootstepFrequency_MetaData), NewProp_CrouchFootstepFrequency_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingDecal = { "NoiseRingDecal", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NoiseRingDecal), Z_Construct_UClass_UDecalComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRingDecal_MetaData), NewProp_NoiseRingDecal_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingMaterialBase = { "NoiseRingMaterialBase", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NoiseRingMaterialBase), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRingMaterialBase_MetaData), NewProp_NoiseRingMaterialBase_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingMID = { "NoiseRingMID", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NoiseRingMID), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRingMID_MetaData), NewProp_NoiseRingMID_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingDuration = { "NoiseRingDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NoiseRingDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRingDuration_MetaData), NewProp_NoiseRingDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingProjectionDepth = { "NoiseRingProjectionDepth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NoiseRingProjectionDepth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseRingProjectionDepth_MetaData), NewProp_NoiseRingProjectionDepth_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayAreaMinWS = { "PlayAreaMinWS", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, PlayAreaMinWS), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayAreaMinWS_MetaData), NewProp_PlayAreaMinWS_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayAreaSizeWS = { "PlayAreaSizeWS", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, PlayAreaSizeWS), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayAreaSizeWS_MetaData), NewProp_PlayAreaSizeWS_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_HearingStimuliSourceComp = { "HearingStimuliSourceComp", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, HearingStimuliSourceComp), Z_Construct_UClass_UAIPerceptionStimuliSourceComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingStimuliSourceComp_MetaData), NewProp_HearingStimuliSourceComp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CameraPivot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NormalWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_MovementStateTags,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_MinMovementSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_WalkFootstepLoudness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_WalkFootstepFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunFootstepLoudness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunFootstepFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchFootstepLoudness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_CrouchFootstepFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingDecal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingMaterialBase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingMID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NoiseRingProjectionDepth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayAreaMinWS,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayAreaSizeWS,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_HearingStimuliSourceComp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_APlayerCharacter_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UGameplayTagAssetInterface_NoRegister, (int32)VTABLE_OFFSET(APlayerCharacter, IGameplayTagAssetInterface), false },  // 3636975782
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayerCharacter_Statics::ClassParams = {
	&APlayerCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APlayerCharacter_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlayerCharacter()
{
	if (!Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton, Z_Construct_UClass_APlayerCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlayerCharacter);
APlayerCharacter::~APlayerCharacter() {}
// ********** End Class APlayerCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FNoiseProfile::StaticStruct, Z_Construct_UScriptStruct_FNoiseProfile_Statics::NewStructOps, TEXT("NoiseProfile"), &Z_Registration_Info_UScriptStruct_FNoiseProfile, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNoiseProfile), 1945086431U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlayerCharacter, APlayerCharacter::StaticClass, TEXT("APlayerCharacter"), &Z_Registration_Info_UClass_APlayerCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayerCharacter), 1432328389U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_4074184014(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h__Script_Invisible_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
