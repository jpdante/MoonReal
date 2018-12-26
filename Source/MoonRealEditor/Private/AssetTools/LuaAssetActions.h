// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"

class ULuaScriptAsset;

class FLuaAssetActions : public FAssetTypeActions_Base
{
public:
	FLuaAssetActions(const TSharedRef<ISlateStyle>& InStyle, EAssetTypeCategories::Type InAssetCategory);

	virtual bool CanFilter() override;
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	
private:
	TSharedRef<ISlateStyle> Style;
	EAssetTypeCategories::Type MyAssetCategory;
};
