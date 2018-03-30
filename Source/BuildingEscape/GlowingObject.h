// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GlowingObject.generated.h"

UCLASS()
class BUILDINGESCAPE_API AGlowingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlowingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ToogleGlow(bool IsGlowing);

	UFUNCTION()
		void EnteredObjectRadius(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void LeftObjectRadius(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_Pickup;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BT_Pickup;
	
};
