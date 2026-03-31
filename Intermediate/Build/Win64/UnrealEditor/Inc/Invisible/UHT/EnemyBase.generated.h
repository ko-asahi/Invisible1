// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/EnemyBase.h"

#ifdef INVISIBLE_EnemyBase_generated_h
#error "EnemyBase.generated.h already included, missing '#pragma once' in EnemyBase.h"
#endif
#define INVISIBLE_EnemyBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FEnemyAlertConfig *************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_18_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FEnemyAlertConfig_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FEnemyAlertConfig;
// ********** End ScriptStruct FEnemyAlertConfig ***************************************************

// ********** Begin ScriptStruct FAIInfoData *******************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_105_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAIInfoData_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FAIInfoData;
// ********** End ScriptStruct FAIInfoData *********************************************************

// ********** Begin Class AEnemyBase ***************************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_132_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyBase(); \
	friend struct Z_Construct_UClass_AEnemyBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister(); \
public: \
	DECLARE_CLASS2(AEnemyBase, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AEnemyBase_NoRegister) \
	DECLARE_SERIALIZER(AEnemyBase)


#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_132_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEnemyBase(AEnemyBase&&) = delete; \
	AEnemyBase(const AEnemyBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyBase) \
	NO_API virtual ~AEnemyBase();


#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_129_PROLOG
#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_132_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_132_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h_132_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEnemyBase;

// ********** End Class AEnemyBase *****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Enemy_EnemyBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
