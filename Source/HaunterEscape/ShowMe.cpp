// Fill out your copyright notice in the Description page of Project Settings.

#include "ShowMe.h"


// Sets default values for this component's properties
UShowMe::UShowMe()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShowMe::BeginPlay()
{
	Super::BeginPlay();

	// ...
	PlayerPerson = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


//This searches for the mirror and displays only if player facing mirror
void UShowMe::SearchForMirror()
{
	//Get Player Viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	if(GetWorld()->GetFirstPlayerController() != NULL)
	{
		//PlayerPerson->GetActorEyesViewPoint(OUT PlayerViewPointLocation,
			//								OUT PlayerViewPointRotation);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No controller"));
	}

	//Create vector to get end point of debug line
	FVector DebugLineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;

	


	//Query Parameter Setup
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, PlayerPerson);

	//Ray Cast to detect objects
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		DebugLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor *ActorHit = Hit.GetActor();
	if(ToHit)
		if (ActorHit)
	{
		if (ActorHit == ToHit)
		{
			GetOwner()->SetActorHiddenInGame(0);
		}
		else
		{
			GetOwner()->SetActorHiddenInGame(1);
		}

	}

}



// Called every frame
void UShowMe::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(PlayerPerson))
	{
		GetOwner()->SetActorHiddenInGame(1);
		SearchForMirror();
		//UE_LOG(LogTemp, Warning, TEXT("On Plate"));
	}
	else
	{
		GetOwner()->SetActorHiddenInGame(1);
	}

	
}

