// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IPluginManager.h"
#include "Brushes/SlateImageBrush.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

class FLuaAssetEditorStyle : public FSlateStyleSet
{

public:

	/** Default constructor. */
	FLuaAssetEditorStyle() : FSlateStyleSet("LuaAssetEditorStyle")
	{
		UE_LOG(LogTemp, Warning, TEXT("REGISTRADO COM SUCESSO TEORICAMENTE"))
		const FVector2D Icon16x16(16.0f, 16.0f);
		const FVector2D Icon20x20(20.0f, 20.0f);
		const FVector2D Icon40x40(40.0f, 40.0f);
		const FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("MoonReal"))->GetBaseDir();
		SetContentRoot(BaseDir / TEXT("Content"));
		// set new styles here, for example...
		//Set("TextAssetEditor.FancyButton", new IMAGE_BRUSH("icon_forward_40x", Icon40x40));
		FSlateStyleRegistry::RegisterSlateStyle(*this);
	}

	/** Destructor. */
	~FLuaAssetEditorStyle()
	{
		UE_LOG(LogTemp, Warning, TEXT("[X] DESREGISTRADO COM SUCESSO TEORICAMENTE"))
		FSlateStyleRegistry::UnRegisterSlateStyle(*this);
	}
};


#undef IMAGE_BRUSH