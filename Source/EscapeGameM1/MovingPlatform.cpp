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
	
	GlobalStartLocation = GetActorLocation(); //Set Start Loc at Local Actor Pos
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); //Take pos in global instead of local

}
//**************************************************************

//**************************************************************
void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (activeTriggers > 0) {
		if (HasAuthority()) { //HasAuthority is server side
			FVector Location = GetActorLocation(); //Store Actor Location in const Vec;
			float JourneyLenght = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLenght) { //If Loc of Actor is > than TargetPos then swap.
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); //Normalize de B-A vector;
			Location += Direction * speed * DeltaTime; //Normalize is 1 * speed&DT so move object at that speed;
			SetActorLocation(Location);
		}
	}
	
}

void  AMovingPlatform::AddActiveTrigger() {
	activeTriggers++;
}
void  AMovingPlatform::RemoveActiveTrigger() {
	if(activeTriggers>0)activeTriggers--;
}