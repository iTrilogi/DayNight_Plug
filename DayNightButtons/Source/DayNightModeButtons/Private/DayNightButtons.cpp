// Copyright Epic Games, Inc. All Rights Reserved.

#include "DayNightButtons.h"
#include "DayNightButtonsStyle.h"
#include "DayNightButtonsCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/lightComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Interfaces/IPluginManager.h"
#include "ActorRotator.h"
#include "Engine/World.h"

static const FName NightModeButtonTabName("DayNightButton");

#define LOCTEXT_NAMESPACE "FDayNightModeButtonsModule"

void FDayNightModeButtonsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FDayNightButtonsStyle::Initialize(isNightMode);
	FDayNightButtonsStyle::ReloadTextures();

	FDayNightButtonsCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	AutoPluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDayNightButtonsCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FDayNightModeButtonsModule::PluginButtonClicked),
		FCanExecuteAction());

	AutoPluginCommands->MapAction(
		FDayNightButtonsCommands::Get().AutoPlugin,
		FExecuteAction::CreateRaw(this, &FDayNightModeButtonsModule::AutoPluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDayNightModeButtonsModule::RegisterMenus));
}

void FDayNightModeButtonsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDayNightButtonsStyle::Shutdown();

	FDayNightButtonsCommands::Unregister();
}


void FDayNightModeButtonsModule::PluginButtonClicked()
{
	AActor* FoundActor;
	FoundActor = FindActor(ADirectionalLight::StaticClass());

	ADirectionalLight* Sun = Cast<ADirectionalLight>(FoundActor);

	APostProcessVolume* PPVol;

	if (!isAutoDay) {
		FText DialogText = FText::FromString("First Deactive the AutoDay");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}
	if (isNightMode) {

		isNightMode = false;

		FText DialogText = FText::FromString("Changing to NightMode");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		FDayNightButtonsStyle::Shutdown();
		FDayNightButtonsStyle::Initialize(isNightMode);

		if (FoundActor) {

			Sun->GetLightComponent()->SetIntensity(1.f);
		}

		FoundActor = FindActor(APostProcessVolume::StaticClass());


		if (!FoundActor) {

			DialogText = FText::FromString("PostProcessActor Not Found, Creating a New One");
			FMessageDialog::Open(EAppMsgType::Ok, DialogText);

			FoundActor = AddActor(APostProcessVolume::StaticClass());
		}

		PPVol = Cast<APostProcessVolume>(FoundActor);

		PPVol->Settings.AutoExposureBias = -3.f;
		PPVol->Settings.bOverride_AutoExposureBias = true;
		PPVol->bUnbound = true;
	}

	else if (!isNightMode) {

		isNightMode = true;

		FText DialogText = FText::FromString("Changing to LightMode");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		FDayNightButtonsStyle::Shutdown();
		FDayNightButtonsStyle::Initialize(isNightMode);

		if (FoundActor) {

			Sun->GetLightComponent()->SetIntensity(10.f);

		}

		FoundActor = FindActor(APostProcessVolume::StaticClass());

		if (FoundActor) {

			PPVol = Cast<APostProcessVolume>(FoundActor);
			PPVol->Destroy();
		}

	}
}

void FDayNightModeButtonsModule::AutoPluginButtonClicked()
{
	UWorld* world = GEditor->GetEditorWorldContext().World();
	AActor* FoundActor;

	APostProcessVolume* PPVol;
	FoundActor = FindActor(APostProcessVolume::StaticClass());
	if (FoundActor) {

		FDayNightButtonsStyle::Shutdown();
		FDayNightButtonsStyle::Initialize(!isNightMode);
		isNightMode = true;
		PPVol = Cast<APostProcessVolume>(FoundActor);
		PPVol->Destroy();
	}

	FoundActor = FindActor(AActorRotator::StaticClass());
	AActorRotator* actorRotate = nullptr;

	if (isAutoDay) {

		isAutoDay = false;
		FText DialogText = FText::FromString("AutoDay Activated");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		if (!FoundActor) {
			actorRotate = Cast<AActorRotator>(AddActor(AActorRotator::StaticClass()));
			actorRotate->SetLight(Cast<ADirectionalLight>(FindActor(ADirectionalLight::StaticClass())));
		}
	}
	else if (!isAutoDay) {

		isAutoDay = true;
		FText DialogText = FText::FromString("AutoDay Deactivated");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		if (FoundActor) {

			actorRotate = Cast<AActorRotator>(FoundActor);
			actorRotate->Destroy();
		}
	}
}

void FDayNightModeButtonsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDayNightButtonsCommands::Get().PluginAction, PluginCommands);
			Section.AddMenuEntryWithCommandList(FDayNightButtonsCommands::Get().AutoPlugin, AutoPluginCommands);

		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDayNightButtonsCommands::Get().PluginAction));
				FToolMenuEntry& Second = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDayNightButtonsCommands::Get().AutoPlugin));

				Entry.SetCommandList(PluginCommands);
				Second.SetCommandList(AutoPluginCommands);
			}
		}
	}
}

AActor* FDayNightModeButtonsModule::FindActor(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> FoundActors;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World) {

		UGameplayStatics::GetAllActorsOfClass(World, ActorClass, FoundActors);
		if (FoundActors.Num() > 0) {

			return FoundActors[0];
		}
	}
	return nullptr;
}

AActor* FDayNightModeButtonsModule::AddActor(TSubclassOf<AActor> ActorClass)
{
	ULevel* Level = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();
	return GEditor->AddActor(Level, ActorClass, FTransform());

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDayNightModeButtonsModule, DayNightButtons)