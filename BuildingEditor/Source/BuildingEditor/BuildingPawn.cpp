// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BuildingPawn.h"

// Sets default values
ABuildingPawn::ABuildingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->SetRelativeRotation(FQuat::MakeFromEuler(FVector(45.f, 0, 0)));

	BaseTurnRate = 45.f;
	BaseZoomRate = 100.f;
	InitialPosition = FVector(0, 0, 300.f);
	InitialMaxSpeed = MovementComponent->MaxSpeed;
	bZooming = false;
	ZoomingMaxSpeed = 4000.f;

}

// Called when the game starts or when spawned
void ABuildingPawn::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorLocation(InitialPosition);
}

// Called every frame
void ABuildingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementComponent->MaxSpeed = bZooming ? ZoomingMaxSpeed : InitialMaxSpeed;
}

// Called to bind functionality to input
void ABuildingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABuildingPawn::MoveForward(float scale)
{
	if(Controller){
		FRotator const ControlSpaceRot = Controller->GetControlRotation();
		AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), scale);
	}
}

void ABuildingPawn::MoveRight(float scale)
{
	if (Controller) {
		FRotator const ControlSpaceRot = Controller->GetControlRotation();
		AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), scale);
	}
}

void ABuildingPawn::MoveWorldUp(float scale)
{
	AddMovementInput(FVector::UpVector, scale);
}

void ABuildingPawn::Zoom(float scale)
{
	if (scale > 0)
		bZooming = true;

	CameraComponent->GetForwardVector();
	AddMovementInput(CameraComponent->GetForwardVector() * BaseZoomRate * GetWorld()->GetDeltaSeconds(), scale);
}

void ABuildingPawn::Turn(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

