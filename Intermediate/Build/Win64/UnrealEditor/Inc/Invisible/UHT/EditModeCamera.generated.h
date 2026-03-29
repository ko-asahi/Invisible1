// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Camera/EditModeCamera.h"

#ifdef INVISIBLE_EditModeCamera_generated_h
#error "EditModeCamera.generated.h already included, missing '#pragma once' in EditModeCamera.h"
#endif
#define INVISIBLE_EditModeCamera_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AEditModeCamera **********************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AEditModeCamera_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEditModeCamera(); \
	friend struct Z_Construct_UClass_AEditModeCamera_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AEditModeCamera_NoRegister(); \
public: \
	DECLARE_CLASS2(AEditModeCamera, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AEditModeCamera_NoRegister) \
	DECLARE_SERIALIZER(AEditModeCamera)


#define FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEditModeCamera(AEditModeCamera&&) = delete; \
	AEditModeCamera(const AEditModeCamera&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEditModeCamera); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEditModeCamera); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEditModeCamera) \
	NO_API virtual ~AEditModeCamera();


#define FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_18_PROLOG
#define FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_21_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEditModeCamera;

// ********** End Class AEditModeCamera ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Camera_EditModeCamera_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
