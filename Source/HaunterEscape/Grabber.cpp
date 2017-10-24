// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#define OUT

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

	// ...
	GetThingsNeededtoMove();
}


void UGrabber::Grab()
{
	
	auto hitResult = GetBodyOnHit();
	
	if (hitResult.GetActor())
	{
		auto ComponentToGrab = hitResult.GetComponent();
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::GetThingsNeededtoMove()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("Phy Ready"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Physics Handle"))
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{

		InputComponent->BindAction("Open", IE_Pressed, this, &UGrabber::Grab);

		InputComponent->BindAction("Open", IE_Released, this, &UGrabber::Release);
		UE_LOG(LogTemp, Warning, TEXT("Inp Ready"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Comp."))
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLoc,
		OUT PlayerViewPointRot
	);

	FVector TraceEnd = PlayerViewPointLoc + PlayerViewPointRot.Vector()*Length;



	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(TraceEnd);
	}



	// ...
}

FHitResult UGrabber::GetBodyOnHit()
{
	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLoc,
		OUT PlayerViewPointRot
	);
	UE_LOG(LogTemp, Warning, TEXT("Your Location : %s and Rotation : %s "), *PlayerViewPointLoc.ToString(),*PlayerViewPointRot.ToString() )

	FVector TraceEnd = PlayerViewPointLoc + PlayerViewPointRot.Vector()*Length;
	UE_LOG(LogTemp, Warning, TEXT("Trace End at : %s "), *TraceEnd.ToString())
	FHitResult Hit;
	FCollisionQueryParams CollisionParam(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLoc,
		TraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionParam
	);
	AActor *ActorHit = Hit.GetActor();
	
	return Hit;
}