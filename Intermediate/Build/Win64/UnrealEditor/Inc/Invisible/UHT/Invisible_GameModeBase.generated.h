// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Invisible_GameModeBase.h"

#ifdef INVISIBLE_Invisible_GameModeBase_generated_h
#error "Invisible_GameModeBase.generated.h already included, missing '#pragma once' in Invisible_GameModeBase.h"
#endif
#define INVISIBLE_Invisible_GameModeBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInvisible_GameModeBase **************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AInvisible_GameModeBase_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInvisible_GameModeBase(); \
	friend struct Z_Construct_UClass_AInvisible_GameModeBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AInvisible_GameModeBase_NoRegister(); \
public: \
	DECLARE_CLASS2(AInvisible_GameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AInvisible_GameModeBase_NoRegister) \
	DECLARE_SERIALIZER(AInvisible_GameModeBase)


#define FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInvisible_GameModeBase(AInvisible_GameModeBase&&) = delete; \
	AInvisible_GameModeBase(const AInvisible_GameModeBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInvisible_GameModeBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInvisible_GameModeBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInvisible_GameModeBase) \
	NO_API virtual ~AInvisible_GameModeBase();


#define FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_15_PROLOG
#define FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_18_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInvisible_GameModeBase;

// ********** End Class AInvisible_GameModeBase ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Invisible_GameModeBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
