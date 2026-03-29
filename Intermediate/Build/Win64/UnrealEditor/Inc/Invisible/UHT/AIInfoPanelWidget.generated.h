// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/AIInfoPanelWidget.h"

#ifdef INVISIBLE_AIInfoPanelWidget_generated_h
#error "AIInfoPanelWidget.generated.h already included, missing '#pragma once' in AIInfoPanelWidget.h"
#endif
#define INVISIBLE_AIInfoPanelWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AEnemyBase;
struct FAIInfoData;

// ********** Begin Class UAIInfoPanelWidget *******************************************************
#define FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_CALLBACK_WRAPPERS
INVISIBLE_API UClass* Z_Construct_UClass_UAIInfoPanelWidget_NoRegister();

#define FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAIInfoPanelWidget(); \
	friend struct Z_Construct_UClass_UAIInfoPanelWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVISIBLE_API UClass* Z_Construct_UClass_UAIInfoPanelWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(UAIInfoPanelWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Invisible"), Z_Construct_UClass_UAIInfoPanelWidget_NoRegister) \
	DECLARE_SERIALIZER(UAIInfoPanelWidget)


#define FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAIInfoPanelWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAIInfoPanelWidget(UAIInfoPanelWidget&&) = delete; \
	UAIInfoPanelWidget(const UAIInfoPanelWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAIInfoPanelWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAIInfoPanelWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAIInfoPanelWidget) \
	NO_API virtual ~UAIInfoPanelWidget();


#define FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_13_PROLOG
#define FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_CALLBACK_WRAPPERS \
	FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_INCLASS_NO_PURE_DECLS \
	FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAIInfoPanelWidget;

// ********** End Class UAIInfoPanelWidget *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
