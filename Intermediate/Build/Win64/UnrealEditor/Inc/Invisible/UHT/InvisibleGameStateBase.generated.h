// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InvisibleGameStateBase.h"

#ifdef INVISIBLE_InvisibleGameStateBase_generated_h
#error "InvisibleGameStateBase.generated.h already included, missing '#pragma once' in InvisibleGameStateBase.h"
#endif
#define INVISIBLE_InvisibleGameStateBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnGlobalHearingRangeChanged ******************************************
#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_14_DELEGATE \
INVISIBLE_API void FOnGlobalHearingRangeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnGlobalHearingRangeChanged, float NewRange);


// ********** End Delegate FOnGlobalHearingRangeChanged ********************************************

// ********** Begin Class AInvisibleGameStateBase **************************************************
#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetGlobalHearingRange); \
	DECLARE_FUNCTION(execSetGlobalHearingRange);


INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleGameStateBase_NoRegister();

#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInvisibleGameStateBase(); \
	friend struct Z_Construct_UClass_AInvisibleGameStateBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleGameStateBase_NoRegister(); \
public: \
	DECLARE_CLASS2(AInvisibleGameStateBase, AGameStateBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AInvisibleGameStateBase_NoRegister) \
	DECLARE_SERIALIZER(AInvisibleGameStateBase)


#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AInvisibleGameStateBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInvisibleGameStateBase(AInvisibleGameStateBase&&) = delete; \
	AInvisibleGameStateBase(const AInvisibleGameStateBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInvisibleGameStateBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInvisibleGameStateBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AInvisibleGameStateBase) \
	NO_API virtual ~AInvisibleGameStateBase();


#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_16_PROLOG
#define FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInvisibleGameStateBase;

// ********** End Class AInvisibleGameStateBase ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
