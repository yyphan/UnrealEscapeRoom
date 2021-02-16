// Yao Yifan 2021

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
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

	// check for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physics handle component at the start of game."), *GetOwner()->GetName());
	}

	// check for input components
	GrabInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if(GrabInput)
	{
		GrabInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		GrabInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get and log player viewpoint
	FVector PlayerVPLocation = GetOwner()->GetActorLocation();
	FRotator PlayerVPRotation = GetOwner()->GetActorRotation();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation, 
		OUT PlayerVPRotation
	);

	// logging out to test
	// UE_LOG(LogTemp, Warning, TEXT("VP Location is %s"), *PlayerVPLocation.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("VP Direction is %s"), *PlayerVPRotation.ToString());

	// Draw a line from player 
	FVector LineTraceEnd = PlayerVPLocation + PlayerVPRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(), 
		PlayerVPLocation, 
		LineTraceEnd, 
		FColor(0, 255, 0), 
		false, 
		0.f,
		0,
		5.f
	);

	FHitResult Hit;
	// Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerVPLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits
	AActor* HitActor = Hit.GetActor();
	if(HitActor)
	{
		FString HitName = HitActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("The actor being hit is %s"), *HitName);
	}
}
