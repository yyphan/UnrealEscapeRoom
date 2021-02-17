// Yao Yifan 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Open Door Function
	void OpenDoor(float DeltaTime);
	// Close Door Function
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	

private:
	float InitialYaw, CurrentYaw, TargetYaw;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 40.f;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 60.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenVelocity = 1.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseVelocity = 0.5f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorClosedDelay = 0.1f;

};
