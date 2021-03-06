// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMassOfActors();
	float CurrentYaw = 0.f, InitialYaw = 0.f, TimerStartClock = 0.f;
	AActor* ActorThatOpens = nullptr;
	bool closed = true;
	UPROPERTY() UAudioComponent* AudioComponent = nullptr;
	UPROPERTY(EditAnywhere) float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere) float DoorOpenDelay = 1.f;
	UPROPERTY(EditAnywhere) float MassThreshold = 10.f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PreasurePlate = nullptr;
};
