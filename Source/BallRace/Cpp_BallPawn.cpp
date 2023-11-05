// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_BallPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACpp_BallPawn::ACpp_BallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACpp_BallPawn::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* playerCtrl = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCtrl->GetLocalPlayer());
		subsystem->ClearAllMappings();
		subsystem->AddMappingContext(MappingContext,0);
	}
	
	SphereMesh = FindComponentByClass<UStaticMeshComponent>();
	SpringArm = FindComponentByClass<USpringArmComponent>();
	Camera = FindComponentByClass<UCameraComponent>();
}

// Called every frame
void ACpp_BallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACpp_BallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* InputComp=Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		InputComp->BindAction(MovementAction,ETriggerEvent::Triggered,this, &ACpp_BallPawn::OnMovement);
		InputComp->BindAction(MouseMovement,ETriggerEvent::Triggered,this, &ACpp_BallPawn::OnMouseMovement);
	}

}

void ACpp_BallPawn::OnMovement(const FInputActionValue& value)
{
	FInputActionValue::Axis2D inputValue = value.Get<FInputActionValue::Axis2D>();
    FVector forwardVector = Camera->GetForwardVector();
	forwardVector.Z = 0;
	forwardVector.Normalize();

	FVector movementVector = inputValue.X * Camera->GetForwardVector() + inputValue.Y * Camera->GetRightVector();
	
	SphereMesh->AddForce(movementVector);
	UE_LOG(LogTemp, Warning, TEXT("Input Working %f,%f"), inputValue.X,inputValue.Y);
}

void ACpp_BallPawn::OnMouseMovement(const FInputActionValue& value)
{
	FInputActionValue::Axis2D inputValue = value.Get<FInputActionValue::Axis2D>();
	SpringArm->AddLocalRotation(FRotator(inputValue.Y,inputValue.X,0));
	FRotator springArmRotation = SpringArm->GetRelativeRotation();
	SpringArm->SetRelativeRotation(FRotator(springArmRotation.Pitch,springArmRotation.Yaw,0));
	UE_LOG(LogTemp, Warning, TEXT("Input Working %f,%f"), inputValue.X,inputValue.Y);
}

 
