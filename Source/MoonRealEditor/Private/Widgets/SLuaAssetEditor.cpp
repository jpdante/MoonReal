// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SLuaAssetEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "LuaScriptAsset.h"
#include "UObject/Class.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

/*#include "TextAssetEditorSettings.h"*/


#define LOCTEXT_NAMESPACE "SLuaAssetEditor"


/* STextAssetEditor interface
 *****************************************************************************/

SLuaAssetEditor::~SLuaAssetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SLuaAssetEditor::Construct(const FArguments& InArgs, ULuaScriptAsset* InTextAsset, const TSharedRef<ISlateStyle>& InStyle)
{
	ScriptAsset = InTextAsset;

/*	auto Settings = GetDefault<ULuaAssetEditorSettings>();*/

	ChildSlot
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
// 			.BackgroundColor((Settings != nullptr) ? Settings->BackgroundColor : FLinearColor::White)
// 		.Font((Settings != nullptr) ? Settings->Font : FSlateFontInfo())
// 		.ForegroundColor((Settings != nullptr) ? Settings->ForegroundColor : FLinearColor::Black)
// 		.Margin((Settings != nullptr) ? Settings->Margin : 4.0f)
		.OnTextChanged(this, &SLuaAssetEditor::HandleEditableTextBoxTextChanged)
		.OnTextCommitted(this, &SLuaAssetEditor::HandleEditableTextBoxTextCommitted)
		.Text(ScriptAsset->LuaScript)
		]
		];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SLuaAssetEditor::HandleTextAssetPropertyChanged);
}


/* STextAssetEditor callbacks
 *****************************************************************************/

void SLuaAssetEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	ScriptAsset->MarkPackageDirty();
}


void SLuaAssetEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	ScriptAsset->LuaScript = EditableTextBox->GetText();
}


void SLuaAssetEditor::HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == ScriptAsset)
	{
		EditableTextBox->SetText(ScriptAsset->LuaScript);
	}
}


#undef LOCTEXT_NAMESPACE