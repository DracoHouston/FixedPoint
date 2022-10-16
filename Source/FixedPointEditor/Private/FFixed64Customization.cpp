// Copyright Epic Games, Inc. All Rights Reserved.

#include "FFixed64Customization.h"
#include "FixedPointNumbers.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SNumericEntryBox.h"

void FFixed64Customization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TSharedPtr<SNumericEntryBox<double>> ValueBox;
	TSharedPtr<IPropertyHandle> ValueHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FFixed64, Value));
	HeaderRow.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Left)
		[
			SAssignNew(ValueBox, SNumericEntryBox<double>)
			.IsEnabled(TAttribute<bool>::CreateLambda([PropertyHandle]()
			{
				return PropertyHandle->IsEditable();
			}))
			.EditableTextBoxStyle(&FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox"))
			.Value_Lambda([ValueHandle]
			{
				int64 result = 0;
				if (ValueHandle->GetValue(result) == FPropertyAccess::Result::Success)
				{
					return (double)FFixed64::MakeFromRawInt(result);
				}
				return 0.0;
			})
			.OnValueCommitted_Lambda([ValueHandle](double NewValue, ETextCommit::Type CommitType)
			{
				FFixed64 result = FFixed64(NewValue);
				ValueHandle->SetValue(result.Value);
			})
		]
	];
}
