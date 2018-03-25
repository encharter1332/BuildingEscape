// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	FindInputComponent();
}

void UGrabber::Grab() {
	//Get The nearest object
	auto HitResult = GetFirstPhysicsBodyInReach();
	//Take the component from the Hit
	UPrimitiveComponent  *ComponentToGrab = HitResult.GetComponent();
	//Take Actor from the Hit
	auto ActorHit = HitResult.GetActor();

	//IF someting is hit Grab
	if (ActorHit)
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, HitResult.Location,true);
}

void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND ON %s"), *GetOwner()->GetName());
}

void UGrabber::FindInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("INPUT COMPONENT NOT FOUND ON %s"), *GetOwner()->GetName())
	}
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit,GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	
	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

}

FVector UGrabber::GetReachLineEnd() {
	FVector playerViewPoint;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPoint, playerViewPointRotation);
	
	return playerViewPoint;
}

FVector UGrabber::GetReachLineStart()
{
	FVector playerViewPoint;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPoint, playerViewPointRotation);

	return playerViewPoint + playerViewPointRotation.Vector() * Reach;
}
