// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InvisibleHUD.h"

#ifdef INVISIBLE_InvisibleHUD_generated_h
#error "InvisibleHUD.generated.h already included, missing '#pragma once' in InvisibleHUD.h"
#endif
#define INVISIBLE_InvisibleHUD_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInvisibleHUD ************************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleHUD_NoRegister();

#define FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInvisibleHUD(); \
	friend struct Z_Construct_UClass_AInvisibleHUD_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleHUD_NoRegister(); \
public: \
	DECLARE_CLASS2(AInvisibleHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AInvisibleHUD_NoRegister) \
	DECLARE_SERIALIZER(AInvisibleHUD)


#define FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AInvisibleHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInvisibleHUD(AInvisibleHUD&&) = delete; \
	AInvisibleHUD(const AInvisibleHUD&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInvisibleHUD); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInvisibleHUD); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AInvisibleHUD) \
	NO_API virtual ~AInvisibleHUD();


#define FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_12_PROLOG
#define FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_15_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_InvisibleHUD_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInvisibleHUD;

// ********** End Class AInvisibleHUD **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_InvisibleHUD_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
