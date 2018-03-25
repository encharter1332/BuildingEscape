// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Classes/Components/PrimitiveComponent.h"

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

	// Find the playing controller
	owner = GetOwner();
	
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > 30.f) {
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetRealTimeSeconds();
	}
	if (GetWorld()->GetRealTimeSeconds() - lastDoorOpenTime >= doorCloseDelay) {
		CloseDoor();
	}

	
	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	pressurePlate->GetOverlappingActors(OverlappingActors);
	//Iterate through them adding masses
	for (auto& Actor : OverlappingActors) {
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}