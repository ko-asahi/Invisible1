// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InvisiblePlayerController.h"

#ifdef INVISIBLE_InvisiblePlayerController_generated_h
#error "InvisiblePlayerController.generated.h already included, missing '#pragma once' in InvisiblePlayerController.h"
#endif
#define INVISIBLE_InvisiblePlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FLockedAIPath *****************************************************
#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLockedAIPath_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FLockedAIPath;
// ********** End ScriptStruct FLockedAIPath *******************************************************

// ********** Begin Class AInvisiblePlayerController ***********************************************
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerController_NoRegister();

#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInvisiblePlayerController(); \
	friend struct Z_Construct_UClass_AInvisiblePlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AInvisiblePlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AInvisiblePlayerController_NoRegister) \
	DECLARE_SERIALIZER(AInvisiblePlayerController)


#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_35_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AInvisiblePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInvisiblePlayerController(AInvisiblePlayerController&&) = delete; \
	AInvisiblePlayerController(const AInvisiblePlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInvisiblePlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInvisiblePlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AInvisiblePlayerController) \
	NO_API virtual ~AInvisiblePlayerController();


#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_32_PROLOG
#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_35_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInvisiblePlayerController;

// ********** End Class AInvisiblePlayerController *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_InvisiblePlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
