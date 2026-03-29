// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/Enum/WaypointTypes.h"

#ifdef INVISIBLE_WaypointTypes_generated_h
#error "WaypointTypes.generated.h already included, missing '#pragma once' in WaypointTypes.h"
#endif
#define INVISIBLE_WaypointTypes_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Invisible_Source_Invisible_Public_Enemy_Enum_WaypointTypes_h

// ********** Begin Enum EWaypointBehavior *********************************************************
#define FOREACH_ENUM_EWAYPOINTBEHAVIOR(op) \
	op(EWaypointBehavior::None) \
	op(EWaypointBehavior::LookAround) \
	op(EWaypointBehavior::Wait) 

enum class EWaypointBehavior : uint8;
template<> struct TIsUEnumClass<EWaypointBehavior> { enum { Value = true }; };
template<> INVISIBLE_API UEnum* StaticEnum<EWaypointBehavior>();
// ********** End Enum EWaypointBehavior ***********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
