// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"

//Included from the engine
#include "Components/BoxComponent.h"

//Inculed localy
#include "MovingPlatform.h"

// Sets default values
APressurePad::APressurePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(triggerVolume != nullptr))return; //Always check if nullptr when handly pointers or refs
	RootComponent = triggerVolume;

	
}

// Called when the game starts or when spawned
void APressurePad::BeginPlay()
{
	Super::BeginPlay();
	triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APressurePad::OnOverlapBegin);
	triggerVolume->OnComponentEndOverlap.AddDynamic(this, &APressurePad::OnOverlapEnd);
}

// Called every frame
void APressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePad::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("ACTIVATED"));
	for (AMovingPlatform* platform : platformsToTrigger) {
		platform->AddActiveTrigger();
	}
}

void APressurePad::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	for (AMovingPlatform* platform : platformsToTrigger) {
		platform->RemoveActiveTrigger();
	}
}

