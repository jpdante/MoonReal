// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "LuaAssetThumbnailRenderer.h"
#include "Engine/Texture2D.h"
#include "CanvasTypes.h"
#include "Interfaces/IPluginManager.h"
#include "LuaScriptAsset.h"

ULuaAssetThumbnailRenderer::ULuaAssetThumbnailRenderer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ULuaAssetThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas)
{
	ULuaScriptAsset* asset = Cast<ULuaScriptAsset>(Object);
	if (asset != nullptr)
	{
		UTexture2D* AssetTexture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/MoonReal/LuaAssetLogo.LuaAssetLogo'"), nullptr, LOAD_None, nullptr);
		Canvas->DrawTile((float)X, (float)Y, (float)Width, (float)Height, 0.0f, 0.0f, 1.0f, 1.0f, FLinearColor::White, AssetTexture->Resource, true);
	}
}
