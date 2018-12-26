// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaAssetFactory.h"
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

ULuaAssetFactory::ULuaAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = ULuaScriptAsset::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
	bEditAfterNew = false;
	bText = false;
	Formats.Add(TEXT("lua;Lua Script"));
}

FText ULuaAssetFactory::GetToolTip() const
{
	return FText::FromString(TEXT("Lua Script"));
}

bool ULuaAssetFactory::FactoryCanImport(const FString& Filename)
{
	FString data;
	if (FFileHelper::LoadFileToString(data, *Filename))
	{
		UE_LOG(LogTemp, Error, TEXT("Pode Importar!"));
		return true;
	}
	return false;
}

UObject* ULuaAssetFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UE_LOG(LogTemp, Error, TEXT("Criando Arquivo..."));
	bOutOperationCanceled = false;
	ULuaScriptAsset* Result = nullptr;
	FString luaSource;
	FFileHelper::LoadFileToString(luaSource, *Filename);
	Result = NewObject<ULuaScriptAsset>(InParent, InName, Flags);
	Result->Modify();
	Result->LuaScript = FText::FromString(luaSource);
	Result->PostEditChange();
	return Result;
}