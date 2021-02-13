// Yao Yifan 2021


#include "OpenDoor.h"
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
	TargetYaw += InitialYaw;
	// float MyFloat = 90.f;
	// FRotator CurrentRotaion = GetOwner()->GetActorRotation();
	// FRotator OpenDoor(CurrentRotaion.Pitch, CurrentRotaion.Yaw + MyFloat, CurrentRotaion.Roll);
	// GetOwner()->SetActorRotation(OpenDoor);


	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Change Yaw of OpenDoor
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime*1.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	// Set the Rotation
	GetOwner()->SetActorRotation(DoorRotation);
}

