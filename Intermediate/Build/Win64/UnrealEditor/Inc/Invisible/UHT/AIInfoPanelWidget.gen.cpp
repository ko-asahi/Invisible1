// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/AIInfoPanelWidget.h"
#include "Enemy/EnemyBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAIInfoPanelWidget() {}

// ********** Begin Cross Module References ********************************************************
INVISIBLE_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();
INVISIBLE_API UClass* Z_Construct_UClass_UAIInfoPanelWidget();
INVISIBLE_API UClass* Z_Construct_UClass_UAIInfoPanelWidget_NoRegister();
INVISIBLE_API UScriptStruct* Z_Construct_UScriptStruct_FAIInfoData();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAIInfoPanelWidget Function UpdateAIInfo *********************************
struct AIInfoPanelWidget_eventUpdateAIInfo_Parms
{
	FAIInfoData AIInfoData;
	AEnemyBase* InEnemy;
};
static FName NAME_UAIInfoPanelWidget_UpdateAIInfo = FName(TEXT("UpdateAIInfo"));
void UAIInfoPanelWidget::UpdateAIInfo(FAIInfoData const& AIInfoData, AEnemyBase* InEnemy)
{
	AIInfoPanelWidget_eventUpdateAIInfo_Parms Parms;
	Parms.AIInfoData=AIInfoData;
	Parms.InEnemy=InEnemy;
	UFunction* Func = FindFunctionChecked(NAME_UAIInfoPanelWidget_UpdateAIInfo);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x9b\xb4\xe6\x96\xb0\xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf\n" },
#endif
		{ "ModuleRelativePath", "Public/Enemy/AIInfoPanelWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9b\xb4\xe6\x96\xb0\xe6\x95\x8c\xe4\xba\xba\xe4\xbf\xa1\xe6\x81\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIInfoData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_AIInfoData;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InEnemy;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::NewProp_AIInfoData = { "AIInfoData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIInfoPanelWidget_eventUpdateAIInfo_Parms, AIInfoData), Z_Construct_UScriptStruct_FAIInfoData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIInfoData_MetaData), NewProp_AIInfoData_MetaData) }; // 461720737
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::NewProp_InEnemy = { "InEnemy", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIInfoPanelWidget_eventUpdateAIInfo_Parms, InEnemy), Z_Construct_UClass_AEnemyBase_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::NewProp_AIInfoData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::NewProp_InEnemy,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAIInfoPanelWidget, nullptr, "UpdateAIInfo", Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::PropPointers), sizeof(AIInfoPanelWidget_eventUpdateAIInfo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(AIInfoPanelWidget_eventUpdateAIInfo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UAIInfoPanelWidget Function UpdateAIInfo ***********************************

// ********** Begin Class UAIInfoPanelWidget *******************************************************
void UAIInfoPanelWidget::StaticRegisterNativesUAIInfoPanelWidget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAIInfoPanelWidget;
UClass* UAIInfoPanelWidget::GetPrivateStaticClass()
{
	using TClass = UAIInfoPanelWidget;
	if (!Z_Registration_Info_UClass_UAIInfoPanelWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AIInfoPanelWidget"),
			Z_Registration_Info_UClass_UAIInfoPanelWidget.InnerSingleton,
			StaticRegisterNativesUAIInfoPanelWidget,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UAIInfoPanelWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UAIInfoPanelWidget_NoRegister()
{
	return UAIInfoPanelWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAIInfoPanelWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Enemy/AIInfoPanelWidget.h" },
		{ "ModuleRelativePath", "Public/Enemy/AIInfoPanelWidget.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAIInfoPanelWidget_UpdateAIInfo, "UpdateAIInfo" }, // 1313766757
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAIInfoPanelWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAIInfoPanelWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAIInfoPanelWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAIInfoPanelWidget_Statics::ClassParams = {
	&UAIInfoPanelWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAIInfoPanelWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UAIInfoPanelWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAIInfoPanelWidget()
{
	if (!Z_Registration_Info_UClass_UAIInfoPanelWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAIInfoPanelWidget.OuterSingleton, Z_Construct_UClass_UAIInfoPanelWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAIInfoPanelWidget.OuterSingleton;
}
UAIInfoPanelWidget::UAIInfoPanelWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAIInfoPanelWidget);
UAIInfoPanelWidget::~UAIInfoPanelWidget() {}
// ********** End Class UAIInfoPanelWidget *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAIInfoPanelWidget, UAIInfoPanelWidget::StaticClass, TEXT("UAIInfoPanelWidget"), &Z_Registration_Info_UClass_UAIInfoPanelWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAIInfoPanelWidget), 2556594614U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h__Script_Invisible_4010318815(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_Enemy_AIInfoPanelWidget_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
