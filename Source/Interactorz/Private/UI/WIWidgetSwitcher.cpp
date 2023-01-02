// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIWidgetSwitcher.h"
#include "Interfaces/IUISwitcherListener.h"

void UWIWidgetSwitcher::OnPanelVisible(bool IsVisible)
{
	if (!IsVisible)
	{
		HandlePageClosing(GetActiveWidget());
		return;
	}

	HandlePageOpening(GetActiveWidget());
}

void UWIWidgetSwitcher::PageChange(float Value)
{
	int32 NextPageWidgetIndex = GetActiveWidgetIndex() + Value;
		
	if (IsPageCycling(NextPageWidgetIndex))
	{
		NextPageWidgetIndex = CyclePage(NextPageWidgetIndex);
	}
	
	HandlePageClosing(GetActiveWidget());
	SetActiveWidgetIndex(NextPageWidgetIndex);
	HandlePageOpening(GetActiveWidget());
}

void UWIWidgetSwitcher::HandlePageClosing(UWidget* PreviousWidget)
{
	IIUISwitcherListener* SwitcherListener = Cast<IIUISwitcherListener>(GetActiveWidget());
	
	if (SwitcherListener == nullptr) return;

	SwitcherListener->Execute_OnPageClosed(GetActiveWidget(), GetActiveWidget());
}

void UWIWidgetSwitcher::HandlePageOpening(UWidget* NextWidget)
{
	IIUISwitcherListener* SwitcherListener = Cast<IIUISwitcherListener>(GetActiveWidget());
	
	if (SwitcherListener == nullptr) return;

	SwitcherListener->Execute_OnPageOpened(GetActiveWidget(), GetActiveWidget());
}

bool UWIWidgetSwitcher::IsPageCycling(int32 NextPageIndex)
{
	return NextPageIndex > GetNumWidgets() -1 || NextPageIndex < 0;
}

int32 UWIWidgetSwitcher::CyclePage(int32 NextPageIndex) const
{
	if (NextPageIndex < 0)
	{
		return GetNumWidgets() - 1;
	}

	return 0;	
}