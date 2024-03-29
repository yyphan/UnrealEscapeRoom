// Yao Yifan 2021


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + OpenAngle;

	// Check on audio component
	FindAudioComponent();
	// Check on pressure plate
	FindPressurePlate();
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component"), *GetOwner()->GetName());
		return;
	}
}

void UOpenDoor::FindPressurePlate()
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor Component on it, but no PressurePlate set."), *GetOwner()->GetName());
		return;
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();		
	}
	else
	{
		// If the door has been opened more than DoorCLoseDelay
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - DoorLastOpened >= DoorClosedDelay)
		{	
			CloseDoor(DeltaTime);
		}
	}

	
}

// Open Door Function
void UOpenDoor::OpenDoor(float DeltaTime)
{
	// Change Yaw of OpenDoor
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime*DoorOpenVelocity);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	// Set the Rotation
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if (!AudioComponent) {return;}
	if(!OpenDoorSound){
		AudioComponent->Play();
		OpenDoorSound = true;
		UE_LOG(LogTemp, Warning, TEXT("Opened"));
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// Change Yaw
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime*DoorCloseVelocity);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	// Set the Rotation
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if (!AudioComponent) {return;}
	if(!CloseDoorSound){
		AudioComponent->Play();
		CloseDoorSound = true;
		UE_LOG(LogTemp, Warning, TEXT("Closed"));
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {return TotalMass;}
	PressurePlate->GetOverlappingActors(OverlappingActors);

	// Add up their masses
	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
