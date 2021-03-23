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
    //Get components
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (NULLPROTECT PhysicsHandle)
    {
        UE_LOG(LogTemp, Display, TEXT("Actor '%s' found 'UPhysicsHandleComponent'."), *(GetOwner()->GetName()))
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
    }

    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (NULLPROTECT InputComponent)
    {
        UE_LOG(LogTemp, Display, TEXT("Actor '%s' found 'UInputComponent'."), *(GetOwner()->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UInputComponent'."), *(GetOwner()->GetName()));
    }

	//Input
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
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
    if (NULLPROTECT Hit.GetActor()) UE_LOG(LogTemp, Warning, TEXT("Actor %s was hit with raycast!"), *Hit.GetActor()->GetName());
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grabed."));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released."));
}