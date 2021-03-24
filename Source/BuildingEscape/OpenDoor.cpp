// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT
#define NULLGUARD


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	if (NULLGUARD !PreasurePlate) UE_LOG(LogTemp, Error, TEXT("Actor %s has the OpenDoor componant but is missing a Preasure Plate."), *GetOwner()->GetName());
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (NULLGUARD !ActorThatOpens) UE_LOG(LogTemp, Error, TEXT("Actor '%s' can't find 'PlayerPawn'."), *(GetOwner()->GetName()));
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (NULLGUARD !AudioComponent) UE_LOG(LogTemp, Error, TEXT("Actor '%s' is missing 'UAudioComponent'."), *(GetOwner()->GetName()));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PreasurePlate && GetTotalMassOfActors() > MassThreshold)
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
	if (closed)
	{
		if (NULLGUARD !AudioComponent) UE_LOG(LogTemp, Error, TEXT("MISSING COMPONENT")); return;
		AudioComponent->Play();
		closed = false;
	}
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator ToRotate(0.f, 0.f, 0.f);
	//ToRotate.Yaw = FMath::FInterpConstantTo(InitialYaw, TargetYaw, DeltaTime, 45.f);
	ToRotate.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(ToRotate);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	if (!closed)
	{
		if (NULLGUARD !AudioComponent) return;
		AudioComponent->Play();
		closed = true;
	}
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator ToRotate(0.f, 0.f, 0.f);
	ToRotate.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(ToRotate);
}

float UOpenDoor::GetTotalMassOfActors()
{
	float TotalMass = 0.f;
	TArray<AActor*> ActorsList;
	PreasurePlate->GetOverlappingActors(OUT ActorsList);
	for (int32 i = 0; i < ActorsList.Num(); i++)
	{
		TotalMass += ActorsList[i]->FindComponentByClass<UPrimitiveComponent>()->CalculateMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total weight is %f of a total of %i actors."), TotalMass, ActorsList.Num());
	return TotalMass;
}

