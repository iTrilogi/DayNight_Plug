// Copyright Epic Games, Inc. All Rights Reserved.

#include "DayNightButtonsStyle.h"
#include "DayNightButtons.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FDayNightButtonsStyle::StyleInstance = nullptr;


void FDayNightButtonsStyle::Initialize(bool isNight)
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create(isNight);
	}
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FDayNightButtonsStyle::Shutdown()
{
	if (StyleInstance.IsValid()) {

		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}
}

FName FDayNightButtonsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DayNightButtonsStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);


TSharedRef< FSlateStyleSet > FDayNightButtonsStyle::Create(bool isNight)
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("DayNightButtonsStyle"));


	Style->SetContentRoot(IPluginManager::Get().FindPlugin("DayNightButtons")->GetBaseDir() / TEXT("Resources"));
	Style->Set("DayNightButtons.AutoPlugin", new IMAGE_BRUSH(TEXT("DayNight_2"), Icon20x20));


	Style->Set("DayNightButtons.AutoPlugin", FMargin(0,5));

	if (isNight) {

		Style->SetContentRoot(IPluginManager::Get().FindPlugin("DayNightButtons")->GetBaseDir() / TEXT("Resources"));
		Style->Set("DayNightButtons.PluginAction", new IMAGE_BRUSH(TEXT("Sun"), Icon20x20));
	}
	else {

		Style->SetContentRoot(IPluginManager::Get().FindPlugin("DayNightButtons")->GetBaseDir() / TEXT("Resources"));
		Style->Set("DayNightButtons.PluginAction", new IMAGE_BRUSH(TEXT("Luna"), Icon20x20));
	}

	return Style;
}

void FDayNightButtonsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FDayNightButtonsStyle::Get()
{
	return *StyleInstance;
}
