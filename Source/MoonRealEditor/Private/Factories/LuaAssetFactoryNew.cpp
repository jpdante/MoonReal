// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaAssetFactoryNew.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "Misc/PackageName.h"
#include "LuaScriptAsset.h"
#include "Editor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "PackageTools.h"

ULuaAssetFactoryNew::ULuaAssetFactoryNew(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = ULuaScriptAsset::StaticClass();
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
	bText = false;
}

UObject* ULuaAssetFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<ULuaScriptAsset>(InParent, InClass, InName, Flags);
}


bool ULuaAssetFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}