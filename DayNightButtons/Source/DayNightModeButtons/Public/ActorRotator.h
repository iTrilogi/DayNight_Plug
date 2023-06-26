// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/DirectionalLight.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorRotator.generated.h"

UCLASS()
class DAYNIGHTBUTTONS_API AActorRotator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	AActorRotator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetLight(ADirectionalLight* inlight);
	UPROPERTY(VisibleAnywhere, Category = "Light")
		ADirectionalLight* light;
	UPROPERTY(EditAnywhere, Category = "Light")
		int speedLight = 10;
};
