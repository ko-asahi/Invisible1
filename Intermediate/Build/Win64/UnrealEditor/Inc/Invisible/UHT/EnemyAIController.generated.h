// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/EnemyAIController.h"

#ifdef INVISIBLE_EnemyAIController_generated_h
#error "EnemyAIController.generated.h already included, missing '#pragma once' in EnemyAIController.h"
#endif
#define INVISIBLE_EnemyAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;
struct FAIStimulus;

// ********** Begin Class AEnemyAIController *******************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execExtendInterestHoldTime); \
	DECLARE_FUNCTION(execClearInvestigateRuntimeState); \
	DECLARE_FUNCTION(execGetHearingRange); \
	DECLARE_FUNCTION(execOnTargetPerceptionUpdated); \
	DECLARE_FUNCTION(execHandleGlobalHearingRangeChanged); \
	DECLARE_FUNCTION(execApplyHearingRangeFromGameState); \
	DECLARE_FUNCTION(execSetInjectedPath); \
	DECLARE_FUNCTION(execGetAlertnessNormalized); \
	DECLARE_FUNCTION(execGetAlertness); \
	DECLARE_FUNCTION(execStartDetectionTimer); \
	DECLARE_FUNCTION(execSetAIPaused);


INVISIBLE_API UClass* Z_Construct_UClass_AEnemyAIController_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyAIController(); \
	friend struct Z_Construct_UClass_AEnemyAIController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_AEnemyAIController_NoRegister(); \
public: \
	DECLARE_CLASS2(AEnemyAIController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_AEnemyAIController_NoRegister) \
	DECLARE_SERIALIZER(AEnemyAIController)


#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEnemyAIController(AEnemyAIController&&) = delete; \
	AEnemyAIController(const AEnemyAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyAIController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyAIController) \
	NO_API virtual ~AEnemyAIController();


#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_18_PROLOG
#define FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEnemyAIController;

// ********** End Class AEnemyAIController *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Enemy_EnemyAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
