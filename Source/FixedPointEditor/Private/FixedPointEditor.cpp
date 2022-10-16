// Copyright Epic Games, Inc. All Rights Reserved.

#include "FixedPointEditor.h"
#include "FixedPointTypes.h"
#include "FFixed64Customization.h"

#define LOCTEXT_NAMESPACE "FFixedPointEditorModule"

void FFixedPointEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(FFixed64::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FFixed64Customization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FFixedPointEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FFixed64::StaticStruct()->GetFName());
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFixedPointEditorModule, FixedPointEditor)