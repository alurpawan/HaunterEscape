// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "CheckFan.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTERESCAPE_API UCheckFan : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckFan();

protected:
	// Called when the game starts
	virtual void BeginPlay() override; 
	float GetTotalMassonPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		AActor* ActorToBin;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;
	
};
