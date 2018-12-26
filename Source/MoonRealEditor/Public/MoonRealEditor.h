// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTools/LuaAssetActions.h"
#include "Styles/LuaAssetEditorStyle.h"
#include "Containers/Array.h"
#include "Modules/ModuleInterface.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"

class FMoonRealEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	void RegisterAssetTools();
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
    void UnregisterAssetTools();

private:

	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
	TSharedPtr<FSlateStyleSet> StyleSet;
	TSharedPtr<ISlateStyle> Style;
	EAssetTypeCategories::Type LuaAssetCategoryBit;
};
