// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT
#define NULLGUARD

#pragma region Setup
void UGrabber::SetupPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (NULLGUARD !PhysicsHandle)
    {
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
    }
}

void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (NULLGUARD !InputComponent)
    {
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UInputComponent'."), *(GetOwner()->GetName()));
    }

	//Binding
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}
#pragma endregion Setup

#pragma region Unreal Methods
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    SetupPhysicsHandle();
    SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (NULLGUARD !PhysicsHandle) UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
    PhysicsHandle->SetTargetLocation(GetTargetPos());
}
#pragma endregion Unreal Methods


void UGrabber::Grab()
{
    FHitResult Hit = GetActorWithinReach();
    if (NULLGUARD Hit.GetActor())
    {
		if (NULLGUARD !PhysicsHandle) UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
		PhysicsHandle->GrabComponent(Hit.GetComponent(), NAME_None, GetTargetPos(), false);
    }
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
	if (NULLGUARD !PhysicsHandle) UE_LOG(LogTemp, Error, TEXT("Actor '%s' is MISSING component 'UphysicsHandleComponent'."), *(GetOwner()->GetName()));
    PhysicsHandle->ReleaseComponent();
}

#pragma region Get/Set
FHitResult UGrabber::GetActorWithinReach()
{
    //Raycast
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
        Hit,
        GetPlayerViewPos(),
        GetTargetPos(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        FCollisionQueryParams(TEXT(""), false, GetOwner())
    );
    return Hit;
}


FVector UGrabber::GetTargetPos()
{
    FVector PlayerViewPos;
    FRotator PlayerViewRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPos,
		OUT PlayerViewRotator
	);
	return PlayerViewPos + PlayerViewRotator.Vector() * Reach;
}

FVector UGrabber::GetPlayerViewPos()
{
    FVector result;
    FRotator temp;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT result,
        OUT temp
	);
    return result;
}
#pragma endregion Get/Set
