// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	
}
//**************************************************************

//**************************************************************
void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (HasAuthority()) { //HasAuthority is server side
		FVector Location = GetActorLocation(); //Store Actor Location in const Vec;
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); //Take pos in global instead of local
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal(); //Normalize de B-A vector;
		Location +=  Direction * speed * DeltaTime; //Normalize is 1 * speed&DT so move object at that speed;
		SetActorLocation(Location);
	}
	

	
}