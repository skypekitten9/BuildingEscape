// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	// ...
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator ToRotate(0.f, 0.f, 0.f);

	//ToRotate.Yaw = FMath::FInterpConstantTo(InitialYaw, TargetYaw, DeltaTime, 45.f);
	ToRotate.Yaw = FMath::FInterpTo(InitialYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(ToRotate);
	UE_LOG(LogTemp, Warning, TEXT("The yaw value is: %f"), GetOwner()->GetActorRotation().Yaw);
}

