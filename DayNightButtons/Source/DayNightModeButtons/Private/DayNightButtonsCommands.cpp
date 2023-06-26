// Copyright Epic Games, Inc. All Rights Reserved.

#include "DayNightButtonsCommands.h"

#define LOCTEXT_NAMESPACE "FDayNightButtonsModule"

void FDayNightButtonsCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "NightModeButton", "Execute NightModeButton action", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AutoPlugin, "AutoDay", "Execute AutoDay action", EUserInterfaceActionType::Button, FInputChord());


}

#undef LOCTEXT_NAMESPACE
