// Fill out your copyright notice in the Description page of Project Settings.

#include "GlowingObject.h"


// Sets default values
AGlowingObject::AGlowingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Pickup = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMPickup"));

	BT_Pickup = CreateDefaultSubobject<UBoxComponent>(TEXT("BTPickup"));
	BT_Pickup->bGenerateOverlapEvents = true;
	BT_Pickup->OnComponentBeginOverlap.AddDynamic(this, &AGlowingObject::EnteredObjectRadius);
	BT_Pickup->OnComponentEndOverlap.AddDynamic(this, &AGlowingObject::LeftObjectRadius);
}

// Called when the game starts or when spawned
void AGlowingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlowingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlowingObject::ToogleGlow(bool IsGlowing)
{
	SM_Pickup->SetRenderCustomDepth(IsGlowing);

}

void AGlowingObject::EnteredObjectRadius(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ToogleGlow(true);
}

void AGlowingObject::LeftObjectRadius(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ToggleGlow(false);
}

