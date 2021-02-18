// Yao Yifan 2021

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#define OUT

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

	FindPhysicsHandle();
	SetupInputComponent();
}

// check for physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physics handle component at the start of game."), *GetOwner()->GetName());
	}
}
// check for input components
void UGrabber::SetupInputComponent()
{
	GrabInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if(GrabInput)
	{
		GrabInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		GrabInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	// Try and reach any actors with physics body collison channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor* ActorHit = HitResult.GetActor();
	// If we hit something, attach the physics handle
	if(ActorHit)
	{	
		// get the component being hit
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		// attach physics handle
		if(!PhysicsHandle){return;}
		PhysicsHandle->GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				GetPlayerReach()
			);
	}
}

void UGrabber::Release()
{
	if(!PhysicsHandle){return;}
	// TODO release the physics handle
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	} 
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PhysicsHandle){return;}
	// If physics handle is attached
	if(PhysicsHandle->GrabbedComponent)
	{
		// Move the object we are holding
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}

// Ray cast
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	// Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

// Get line trace end
FVector UGrabber::GetPlayerReach() const
{
	// Get and log player viewpoint
	FVector PlayerVPLocation = GetOwner()->GetActorLocation();
	FRotator PlayerVPRotation = GetOwner()->GetActorRotation();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation, 
		OUT PlayerVPRotation
	);
	
	return PlayerVPLocation + PlayerVPRotation.Vector() * Reach;
}

//Get Player Location
FVector UGrabber::GetPlayerWorldPos() const
{
	return GetOwner()->GetActorLocation();
}