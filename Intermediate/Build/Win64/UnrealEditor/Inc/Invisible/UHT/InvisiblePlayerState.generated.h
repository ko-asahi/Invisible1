// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InvisiblePlayerState.h"

#ifdef INVISIBLE_InvisiblePlayerState_generated_h
#error "InvisiblePlayerState.generated.h already included, missing '#pragma once' in InvisiblePlayerState.h"
#endif
#define INVISIBLE_InvisiblePlayerState_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInvisiblePlayerState ****************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerState_NoRegister();

#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInvisiblePlayerState(); \
	friend struct Z_Construct_UClass_AInvisiblePlayerState_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AInvisiblePlayerState_NoRegister(); \
public: \
	DECLARE_CLASS2(AInvisiblePlayerState, APlayerState, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AInvisiblePlayerState_NoRegister) \
	DECLARE_SERIALIZER(AInvisiblePlayerState)


#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AInvisiblePlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInvisiblePlayerState(AInvisiblePlayerState&&) = delete; \
	AInvisiblePlayerState(const AInvisiblePlayerState&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInvisiblePlayerState); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInvisiblePlayerState); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AInvisiblePlayerState) \
	NO_API virtual ~AInvisiblePlayerState();


#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_12_PROLOG
#define FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_15_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInvisiblePlayerState;

// ********** End Class AInvisiblePlayerState ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_InvisiblePlayerState_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
