// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Unreal Logic
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//Unreal Logic
	virtual void BeginPlay() override;

private:
	//Variables
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	UPROPERTY(EditAnywhere) float Reach = 100.f;

	//Setup
	void SetupPhysicsHandle();
	void SetupInputComponent();

	//Logic
	void Grab();
	void Release();

	//Get & Set
	FHitResult GetActorWithinReach();
	FVector GetTargetPos();
	FVector GetPlayerViewPos();
};
