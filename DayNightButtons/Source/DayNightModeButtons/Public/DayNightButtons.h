// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Misc/App.h"
#include "GameFramework/Actor.h"


class FToolBarBuilder;
class FMenuBuilder;
static double DeltaTime = 1 / 30.0;


class FDayNightModeButtonsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void AutoPluginButtonClicked();
	//virtual void Tick(float DeltaSeconds) override;
private:

	bool isNightMode = true;
	bool isAutoDay = true;
	void RegisterMenus();
	AActor* FindActor(TSubclassOf<AActor> ActorClass);
	AActor* AddActor(TSubclassOf<AActor> ActorClass);


private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class FUICommandList> AutoPluginCommands;
};
