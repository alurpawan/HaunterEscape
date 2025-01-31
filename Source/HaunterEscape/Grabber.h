// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTERESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	void GetThingsNeededtoMove();
	FHitResult GetBodyOnHit();

private:

	float Length = 100.f;
	
	//UPROPERTY(EditAnywhere)
		//AActor* ActorToMove;

		UPhysicsHandleComponent* PhysicsHandle = nullptr;
		UInputComponent* InputComponent = nullptr;
};
