// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


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
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber Report reporting for duty!" ));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector playerViewPoint;
	FRotator playerViewPointRotation;
	float Reach = 100.f;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPoint,playerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Player view is at position %s and rotation is %s"), *playerViewPoint.ToString(), *playerViewPointRotation.ToString());
	FVector LineTraceEnd = playerViewPoint + playerViewPointRotation.Vector() * Reach;
	//Draw a red trace
	DrawDebugLine(GetWorld(), playerViewPoint,LineTraceEnd,FColor(255,0,0),false,0.f,0.f,10.f );
	//Set Up query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	// Line-trace
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit,playerViewPoint,LineTraceEnd,FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParameters);
//	
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
}

