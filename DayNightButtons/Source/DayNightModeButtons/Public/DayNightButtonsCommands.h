// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DayNightButtonsStyle.h"

class FDayNightButtonsCommands : public TCommands<FDayNightButtonsCommands>
{
public:

	FDayNightButtonsCommands()
		: TCommands<FDayNightButtonsCommands>(TEXT("DayNightButtons"), NSLOCTEXT("Contexts", "DayNightButtons", "DayNightButtons Plugin"), NAME_None, FDayNightButtonsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
	TSharedPtr< FUICommandInfo > AutoPlugin;

};
