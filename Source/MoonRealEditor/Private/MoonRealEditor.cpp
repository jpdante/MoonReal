// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MoonRealEditor.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetRegistryModule.h"
#include "AssetTools/LuaAssetActions.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Styles/MoonRealStyle.h"
#include "LuaScriptAsset.h"
#include "Thumbnails/LuaAssetThumbnailRenderer.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FMoonRealEditorModule"

void FMoonRealEditorModule::StartupModule()
{
	Style = MakeShareable(new FLuaAssetEditorStyle());
	FMoonRealStyle::Initialize();
	RegisterAssetTools();
	UThumbnailManager::Get().RegisterCustomRenderer(ULuaScriptAsset::StaticClass(), ULuaAssetThumbnailRenderer::StaticClass());
}

void FMoonRealEditorModule::ShutdownModule()
{
	UThumbnailManager::Get().UnregisterCustomRenderer(ULuaScriptAsset::StaticClass());
	FMoonRealStyle::Shutdown();
	UnregisterAssetTools();
}

void FMoonRealEditorModule::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	LuaAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Lua")), LOCTEXT("LuaAssetCategory", "Lua Scripting"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FLuaAssetActions(Style.ToSharedRef(), LuaAssetCategoryBit)));
}

void FMoonRealEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

void FMoonRealEditorModule::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMoonRealEditorModule, MoonRealEditor)