// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT
#define NULLPROTECT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (NULLPROTECT PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' is missing a 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
    //Raycast
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPos,
        OUT PlayerViewRotator
    );
    FVector TargetPos = PlayerViewPos + PlayerViewRotator.Vector() * Reach;
    DrawDebugLine(
        GetWorld(),
        PlayerViewPos,
        TargetPos,
        FColor(0.f, 255.f, 0.f),
        false,
        0.f,
        0,
        3
    );
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
        Hit,
        PlayerViewPos,
        TargetPos,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        FCollisionQueryParams(TEXT(""), false, GetOwner())
    );
    if (NULLPROTECT Hit.GetActor()) UE_LOG(LogTemp, Warning, TEXT("Actor %s was hit with raycast!"), *Hit.GetActor()->GetName())
}

