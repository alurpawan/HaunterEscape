// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "ShowMe.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTERESCAPE_API UShowMe : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShowMe();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SearchForMirror();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	AActor* PlayerPerson;
	float Reach = 100.f;
	UPROPERTY(EditAnywhere)
		AActor* ToHit;
};
