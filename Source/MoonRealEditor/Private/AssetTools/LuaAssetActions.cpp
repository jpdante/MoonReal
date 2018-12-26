// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaAssetActions.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LuaScriptAsset.h"
#include "Styling/SlateStyle.h"
#include "Toolkits/LuaAssetEditorToolkit.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

/* FAssetTypeActions_Base overrides
 *****************************************************************************/

FLuaAssetActions::FLuaAssetActions(const TSharedRef<ISlateStyle>& InStyle, EAssetTypeCategories::Type InAssetCategory) : MyAssetCategory(InAssetCategory), Style(InStyle)
{
}

bool FLuaAssetActions::CanFilter()
{
	return true;
}

uint32 FLuaAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc | MyAssetCategory;
}

FText FLuaAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_TextAsset", "Lua Script");
}

UClass* FLuaAssetActions::GetSupportedClass() const
{
	return ULuaScriptAsset::StaticClass();
}

FColor FLuaAssetActions::GetTypeColor() const
{
	return FColor::FromHex(TEXT("#00007C"));
}

bool FLuaAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return false;
}

void FLuaAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto TextAsset = Cast<ULuaScriptAsset>(*ObjIt);

		if (TextAsset != nullptr)
		{
			TSharedRef<FLuaAssetEditorToolkit> EditorToolkit = MakeShareable(new FLuaAssetEditorToolkit(Style));
			EditorToolkit->Initialize(TextAsset, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE