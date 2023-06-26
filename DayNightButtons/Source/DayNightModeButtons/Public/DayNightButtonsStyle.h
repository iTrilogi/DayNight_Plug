// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"
#include <fstream> 

class FDayNightButtonsStyle
{
public:

	static void Initialize(bool isNight);

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	static TSharedRef< class FSlateStyleSet > Create(bool isNight);


private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;

};