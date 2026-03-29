// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Camera/EditModeCamera.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEditModeCamera() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_AEditModeCamera();
INVISIBLE_API UClass* Z_Construct_UClass_AEditModeCamera_NoRegister();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AEditModeCamera **********************************************************
void AEditModeCamera::StaticRegisterNativesAEditModeCamera()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AEditModeCamera;
UClass* AEditModeCamera::GetPrivateStaticClass()
{
	using TClass = AEditModeCamera;
	if (!Z_Registration_Info_UClass_AEditModeCamera.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("EditModeCamera"),
			Z_Registration_Info_UClass_AEditModeCamera.InnerSingleton,
			StaticRegisterNativesAEditModeCamera,
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
	return Z_Registration_Info_UClass_AEditModeCamera.InnerSingleton;
}
UClass* Z_Construct_UClass_AEditModeCamera_NoRegister()
{
	return AEditModeCamera::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEditModeCamera_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe7\x9b\xb8\xe6\x9c\xba\n */" },
#endif
		{ "IncludePath", "Camera/EditModeCamera.h" },
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbc\x96\xe8\xbe\x91\xe6\xa8\xa1\xe5\xbc\x8f\xe7\x9b\xb8\xe6\x9c\xba" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe7\xbb\x84\xe4\xbb\xb6\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundRingMesh_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\xbc\xa0\xe6\xa0\x87\xe6\x8a\x95\xe5\xbd\xb1\xe6\x8c\x87\xe7\xa4\xba\xe5\x99\xa8\xe7\xbb\x84\xe4\xbb\xb6\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\xbc\xa0\xe6\xa0\x87\xe6\x8a\x95\xe5\xbd\xb1\xe6\x8c\x87\xe7\xa4\xba\xe5\x99\xa8\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPitch_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x94\x9f\xe6\x88\x90\xe6\x97\xb6\xe7\x9b\xb8\xe6\x9c\xba\xe4\xbf\xaf\xe8\xa7\x86\xe8\xa7\x92\n" },
#endif
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\x9f\xe6\x88\x90\xe6\x97\xb6\xe7\x9b\xb8\xe6\x9c\xba\xe4\xbf\xaf\xe8\xa7\x86\xe8\xa7\x92" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPanSpeed_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe5\xb9\xb3\xe7\xa7\xbb\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe5\xb9\xb3\xe7\xa7\xbb\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraOrbitSpeed_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe6\x97\x8b\xe8\xbd\xac\xe9\x80\x9f\xe5\xba\xa6\n" },
#endif
		{ "ModuleRelativePath", "Public/Camera/EditModeCamera.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe6\x97\x8b\xe8\xbd\xac\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GroundRingMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraPitch;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraPanSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraOrbitSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEditModeCamera>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditModeCamera_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEditModeCamera, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEditModeCamera_Statics::NewProp_GroundRingMesh = { "GroundRingMesh", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEditModeCamera, GroundRingMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundRingMesh_MetaData), NewProp_GroundRingMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraPitch = { "CameraPitch", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEditModeCamera, CameraPitch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPitch_MetaData), NewProp_CameraPitch_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraPanSpeed = { "CameraPanSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEditModeCamera, CameraPanSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPanSpeed_MetaData), NewProp_CameraPanSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraOrbitSpeed = { "CameraOrbitSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEditModeCamera, CameraOrbitSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraOrbitSpeed_MetaData), NewProp_CameraOrbitSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEditModeCamera_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditModeCamera_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditModeCamera_Statics::NewProp_GroundRingMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraPitch,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraPanSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEditModeCamera_Statics::NewProp_CameraOrbitSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEditModeCamera_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AEditModeCamera_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEditModeCamera_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEditModeCamera_Statics::ClassParams = {
	&AEditModeCamera::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AEditModeCamera_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AEditModeCamera_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEditModeCamera_Statics::Class_MetaDataParams), Z_Construct_UClass_AEditModeCamera_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEditModeCamera()
{
	if (!Z_Registration_Info_UClass_AEditModeCamera.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEditModeCamera.OuterSingleton, Z_Construct_UClass_AEditModeCamera_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEditModeCamera.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEditModeCamera);
AEditModeCamera::~AEditModeCamera() {}
// ********** End Class AEditModeCamera ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEditModeCamera, AEditModeCamera::StaticClass, TEXT("AEditModeCamera"), &Z_Registration_Info_UClass_AEditModeCamera, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEditModeCamera), 16777415U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h__Script_Invisible_1237015684(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
