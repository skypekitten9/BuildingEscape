// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	//Error-handling
	if (!PreasurePlate) UE_LOG(LogTemp, Error, TEXT("Actor %s has the OpenDoor componant but is missing a Preasure Plate."), *GetOwner()->GetName());
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PreasurePlate && PreasurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		TimerStartClock = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - TimerStartClock > DoorOpenDelay) CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator ToRotate(0.f, 0.f, 0.f);
	//ToRotate.Yaw = FMath::FInterpConstantTo(InitialYaw, TargetYaw, DeltaTime, 45.f);
	ToRotate.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(ToRotate);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator ToRotate(0.f, 0.f, 0.f);
	ToRotate.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(ToRotate);
}

