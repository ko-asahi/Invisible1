// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/PatrolPath.h"

#ifdef INVISIBLE_PatrolPath_generated_h
#error "PatrolPath.generated.h already included, missing '#pragma once' in PatrolPath.h"
#endif
#define INVISIBLE_PatrolPath_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin ScriptStruct FWaypointBinding **************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_29_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FWaypointBinding_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FWaypointBinding;
// ********** End ScriptStruct FWaypointBinding ****************************************************

// ********** Begin ScriptStruct FPatrolWaypointData ***********************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FPatrolWaypointData_Statics; \
	INVISIBLE_API static class UScriptStruct* StaticStruct();


struct FPatrolWaypointData;
// ********** End ScriptStruct FPatrolWaypointData *************************************************

// ********** Begin Class APatrolPath **************************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleWaypointDestroyed);


INVISIBLE_API UClass* Z_Construct_UClass_APatrolPath_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPatrolPath(); \
	friend struct Z_Construct_UClass_APatrolPath_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_APatrolPath_NoRegister(); \
public: \
	DECLARE_CLASS2(APatrolPath, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_APatrolPath_NoRegister) \
	DECLARE_SERIALIZER(APatrolPath)


#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APatrolPath(APatrolPath&&) = delete; \
	APatrolPath(const APatrolPath&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APatrolPath); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APatrolPath); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APatrolPath) \
	NO_API virtual ~APatrolPath();


#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_80_PROLOG
#define FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h_83_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APatrolPath;

// ********** End Class APatrolPath ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Enemy_PatrolPath_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
