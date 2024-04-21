// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "BuildingPawn.generated.h"

UCLASS()
class BUILDINGEDITOR_API ABuildingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuildingPawn();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingPawn")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingPawn")
	float BaseZoomRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingPawn")
	FVector InitialPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingPawn")
	float ZoomingMaxSpeed;

private:
	UPROPERTY()
	bool bZooming;

	UPROPERTY()
	float InitialMaxSpeed;

protected:
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	USceneComponent* Root;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	/**** Function ***/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BuildingPawn")
	void MoveForward(float scale);

	UFUNCTION(BlueprintCallable, Category = "BuildingPawn")
	void MoveRight(float scale);

	UFUNCTION(BlueprintCallable, Category = "BuildingPawn")
	void MoveWorldUp(float scale);

	UFUNCTION(BlueprintCallable, Category = "BuildingPawn")
	void Zoom(float scale);

	UFUNCTION(BlueprintCallable, Category = "BuildingPawn")
	void Turn(float rate);



};
