// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRotator.h"

// Sets default values

AActorRotator::AActorRotator()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorRotator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (light) {
		//UE_LOG(LogTemp, Warning, TEXT("It Works!!!"));
		light->AddActorLocalRotation(FRotator(speedLight * DeltaTime, 0, 0));
	}
}

void AActorRotator::SetLight(ADirectionalLight* inlight)
{
	if (inlight) {
		light = inlight;
		light->SetActorRelativeRotation(FRotator(-90, 0, 0));
	}
}

