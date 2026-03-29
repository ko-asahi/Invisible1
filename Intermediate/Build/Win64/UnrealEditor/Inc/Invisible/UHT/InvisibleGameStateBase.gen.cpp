// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InvisibleGameStateBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInvisibleGameStateBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleGameStateBase();
INVISIBLE_API UClass* Z_Construct_UClass_AInvisibleGameStateBase_NoRegister();
INVISIBLE_API UFunction* Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_Invisible();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnGlobalHearingRangeChanged ******************************************
struct Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics
{
	struct _Script_Invisible_eventOnGlobalHearingRangeChanged_Parms
	{
		float NewRange;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */// \xe5\x88\x9b\xe5\xbb\xba\xe5\xae\x8f\xef\xbc\x8c\xe7\x94\xa8\xe4\xba\x8e\xe5\xb9\xbf\xe6\x92\xad\xe5\xaf\xb9\xe4\xba\x8e""ai\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe7\x9a\x84\xe4\xbf\xae\xe6\x94\xb9\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "// \xe5\x88\x9b\xe5\xbb\xba\xe5\xae\x8f\xef\xbc\x8c\xe7\x94\xa8\xe4\xba\x8e\xe5\xb9\xbf\xe6\x92\xad\xe5\xaf\xb9\xe4\xba\x8e""ai\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe7\x9a\x84\xe4\xbf\xae\xe6\x94\xb9" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::NewProp_NewRange = { "NewRange", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Invisible_eventOnGlobalHearingRangeChanged_Parms, NewRange), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::NewProp_NewRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Invisible, nullptr, "OnGlobalHearingRangeChanged__DelegateSignature", Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::_Script_Invisible_eventOnGlobalHearingRangeChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::_Script_Invisible_eventOnGlobalHearingRangeChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnGlobalHearingRangeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnGlobalHearingRangeChanged, float NewRange)
{
	struct _Script_Invisible_eventOnGlobalHearingRangeChanged_Parms
	{
		float NewRange;
	};
	_Script_Invisible_eventOnGlobalHearingRangeChanged_Parms Parms;
	Parms.NewRange=NewRange;
	OnGlobalHearingRangeChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnGlobalHearingRangeChanged ********************************************

// ********** Begin Class AInvisibleGameStateBase Function GetGlobalHearingRange *******************
struct Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics
{
	struct InvisibleGameStateBase_eventGetGlobalHearingRange_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Hearing" },
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InvisibleGameStateBase_eventGetGlobalHearingRange_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInvisibleGameStateBase, nullptr, "GetGlobalHearingRange", Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::PropPointers), sizeof(Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::InvisibleGameStateBase_eventGetGlobalHearingRange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::InvisibleGameStateBase_eventGetGlobalHearingRange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInvisibleGameStateBase::execGetGlobalHearingRange)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetGlobalHearingRange();
	P_NATIVE_END;
}
// ********** End Class AInvisibleGameStateBase Function GetGlobalHearingRange *********************

// ********** Begin Class AInvisibleGameStateBase Function SetGlobalHearingRange *******************
struct Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics
{
	struct InvisibleGameStateBase_eventSetGlobalHearingRange_Parms
	{
		float NewRange;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AI|Perception|Hearing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// BlueprintCallable\xef\xbc\x8c\xe8\x93\x9d\xe5\x9b\xbe\xe5\x92\x8c\xe4\xbb\xa3\xe7\xa0\x81\xe9\x83\xbd\xe5\x8f\xaf\xe8\xb0\x83\xe7\x94\xa8\xe4\xbf\xae\xe6\x94\xb9\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BlueprintCallable\xef\xbc\x8c\xe8\x93\x9d\xe5\x9b\xbe\xe5\x92\x8c\xe4\xbb\xa3\xe7\xa0\x81\xe9\x83\xbd\xe5\x8f\xaf\xe8\xb0\x83\xe7\x94\xa8\xe4\xbf\xae\xe6\x94\xb9" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::NewProp_NewRange = { "NewRange", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InvisibleGameStateBase_eventSetGlobalHearingRange_Parms, NewRange), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::NewProp_NewRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInvisibleGameStateBase, nullptr, "SetGlobalHearingRange", Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::PropPointers), sizeof(Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::InvisibleGameStateBase_eventSetGlobalHearingRange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::InvisibleGameStateBase_eventSetGlobalHearingRange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInvisibleGameStateBase::execSetGlobalHearingRange)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewRange);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetGlobalHearingRange(Z_Param_NewRange);
	P_NATIVE_END;
}
// ********** End Class AInvisibleGameStateBase Function SetGlobalHearingRange *********************

// ********** Begin Class AInvisibleGameStateBase **************************************************
void AInvisibleGameStateBase::StaticRegisterNativesAInvisibleGameStateBase()
{
	UClass* Class = AInvisibleGameStateBase::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetGlobalHearingRange", &AInvisibleGameStateBase::execGetGlobalHearingRange },
		{ "SetGlobalHearingRange", &AInvisibleGameStateBase::execSetGlobalHearingRange },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInvisibleGameStateBase;
UClass* AInvisibleGameStateBase::GetPrivateStaticClass()
{
	using TClass = AInvisibleGameStateBase;
	if (!Z_Registration_Info_UClass_AInvisibleGameStateBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InvisibleGameStateBase"),
			Z_Registration_Info_UClass_AInvisibleGameStateBase.InnerSingleton,
			StaticRegisterNativesAInvisibleGameStateBase,
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
	return Z_Registration_Info_UClass_AInvisibleGameStateBase.InnerSingleton;
}
UClass* Z_Construct_UClass_AInvisibleGameStateBase_NoRegister()
{
	return AInvisibleGameStateBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInvisibleGameStateBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "InvisibleGameStateBase.h" },
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GlobalHearingRange_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
		{ "ClamMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x85\xa8\xe5\xb1\x80\xe7\xbb\x9f\xe4\xb8\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xa8\xe5\xb1\x80\xe7\xbb\x9f\xe4\xb8\x80\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4" },
#endif
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnGlobalHearingRangeChanged_MetaData[] = {
		{ "Category", "AI|Perception|Hearing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xb9\xbf\xe6\x92\xad\xe5\xaf\xb9\xe4\xba\x8e""ai\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe7\x9a\x84\xe4\xbf\xae\xe6\x94\xb9\n" },
#endif
		{ "ModuleRelativePath", "Public/InvisibleGameStateBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb9\xbf\xe6\x92\xad\xe5\xaf\xb9\xe4\xba\x8e""ai\xe5\x90\xac\xe8\xa7\x89\xe8\x8c\x83\xe5\x9b\xb4\xe7\x9a\x84\xe4\xbf\xae\xe6\x94\xb9" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GlobalHearingRange;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnGlobalHearingRangeChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AInvisibleGameStateBase_GetGlobalHearingRange, "GetGlobalHearingRange" }, // 3946671685
		{ &Z_Construct_UFunction_AInvisibleGameStateBase_SetGlobalHearingRange, "SetGlobalHearingRange" }, // 2160020758
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInvisibleGameStateBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInvisibleGameStateBase_Statics::NewProp_GlobalHearingRange = { "GlobalHearingRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisibleGameStateBase, GlobalHearingRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalHearingRange_MetaData), NewProp_GlobalHearingRange_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AInvisibleGameStateBase_Statics::NewProp_OnGlobalHearingRangeChanged = { "OnGlobalHearingRangeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInvisibleGameStateBase, OnGlobalHearingRangeChanged), Z_Construct_UDelegateFunction_Invisible_OnGlobalHearingRangeChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnGlobalHearingRangeChanged_MetaData), NewProp_OnGlobalHearingRangeChanged_MetaData) }; // 1578962953
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInvisibleGameStateBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisibleGameStateBase_Statics::NewProp_GlobalHearingRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInvisibleGameStateBase_Statics::NewProp_OnGlobalHearingRangeChanged,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleGameStateBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AInvisibleGameStateBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameStateBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Invisible,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleGameStateBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInvisibleGameStateBase_Statics::ClassParams = {
	&AInvisibleGameStateBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AInvisibleGameStateBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleGameStateBase_Statics::PropPointers),
	0,
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInvisibleGameStateBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AInvisibleGameStateBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInvisibleGameStateBase()
{
	if (!Z_Registration_Info_UClass_AInvisibleGameStateBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInvisibleGameStateBase.OuterSingleton, Z_Construct_UClass_AInvisibleGameStateBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInvisibleGameStateBase.OuterSingleton;
}
AInvisibleGameStateBase::AInvisibleGameStateBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInvisibleGameStateBase);
AInvisibleGameStateBase::~AInvisibleGameStateBase() {}
// ********** End Class AInvisibleGameStateBase ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h__Script_Invisible_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInvisibleGameStateBase, AInvisibleGameStateBase::StaticClass, TEXT("AInvisibleGameStateBase"), &Z_Registration_Info_UClass_AInvisibleGameStateBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInvisibleGameStateBase), 3663682914U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h__Script_Invisible_3441401288(TEXT("/Script/Invisible"),
	Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h__Script_Invisible_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Invisible_Source_Invisible_Public_InvisibleGameStateBase_h__Script_Invisible_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
