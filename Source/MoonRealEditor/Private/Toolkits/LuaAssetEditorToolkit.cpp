// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LuaAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "Widgets/SLuaAssetEditor.h"
#include "LuaScriptAsset.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FLuaAssetEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogLuaAssetEditor, Log, All);

namespace TextAssetEditor
{
	static const FName AppIdentifier("LuaAssetEditorApp");
	static const FName TabId("LuaEditor");
}

FLuaAssetEditorToolkit::FLuaAssetEditorToolkit(const TSharedRef<ISlateStyle>& InStyle) : ScriptAsset(nullptr), Style(InStyle)
{ }


FLuaAssetEditorToolkit::~FLuaAssetEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}

void FLuaAssetEditorToolkit::Initialize(ULuaScriptAsset* InScriptAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	ScriptAsset = InScriptAsset;

	// Support undo/redo
	ScriptAsset->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_TextAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.66f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.1f)

				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(TextAssetEditor::TabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.9f)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		TextAssetEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InScriptAsset
	);

	RegenerateMenusAndToolbars();
}

FString FLuaAssetEditorToolkit::GetDocumentationLink() const
{
	return FString(TEXT("https://www.google.com/"));
}

void FLuaAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_TextAssetEditor", "Lua Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(TextAssetEditor::TabId, FOnSpawnTab::CreateSP(this, &FLuaAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::TabId))
		.SetDisplayName(LOCTEXT("TextEditorTabName", "Lua Editor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}

void FLuaAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(TextAssetEditor::TabId);
}

FText FLuaAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Lua Asset Editor");
}


FName FLuaAssetEditorToolkit::GetToolkitFName() const
{
	return FName("LuaAssetEditor");
}


FLinearColor FLuaAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}


FString FLuaAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "LuaAsset ").ToString();
}

void FLuaAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(ScriptAsset);
}

void FLuaAssetEditorToolkit::PostUndo(bool bSuccess)
{ }


void FLuaAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}

TSharedRef<SDockTab> FLuaAssetEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == TextAssetEditor::TabId)
	{
		TabWidget = SNew(SLuaAssetEditor, ScriptAsset, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE