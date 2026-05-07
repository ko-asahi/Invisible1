// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.
#include "SIZZ_Spell_Indicator.h"

#define LOCTEXT_NAMESPACE "FSIZZ_Spell_IndicatorModule"

void FSIZZ_Spell_IndicatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSIZZ_Spell_IndicatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSIZZ_Spell_IndicatorModule, SIZZ_Spell_Indicator)