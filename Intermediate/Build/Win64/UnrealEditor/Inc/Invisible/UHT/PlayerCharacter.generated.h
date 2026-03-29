// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Player/PlayerCharacter.h"

#ifdef INVISIBLE_PlayerCharacter_generated_h
#error "PlayerCharacter.generated.h already included, missing '#pragma once' in PlayerCharacter.h"
#endif
#define INVISIBLE_PlayerCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FNoiseProfile *****************************************************
#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_22_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNoiseProfile_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FNoiseProfile;
// ********** End ScriptStruct FNoiseProfile *******************************************************

// ********** Begin Class APlayerCharacter *********************************************************
#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleGlobalHearingRangeChanged);


INVISIBLE_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerCharacter(); \
	friend struct Z_Construct_UClass_APlayerCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(APlayerCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_APlayerCharacter_NoRegister) \
	DECLARE_SERIALIZER(APlayerCharacter) \
	virtual UObject* _getUObject() const override { return const_cast<APlayerCharacter*>(this); }


#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APlayerCharacter(APlayerCharacter&&) = delete; \
	APlayerCharacter(const APlayerCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerCharacter) \
	NO_API virtual ~APlayerCharacter();


#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_30_PROLOG
#define FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h_33_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APlayerCharacter;

// ********** End Class APlayerCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Player_PlayerCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
