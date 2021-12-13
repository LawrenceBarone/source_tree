// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PressurePad.h"
#include "MenuSystem/MainMenu.h"
//Create a Game Instance Constructeur and Init it on Play
UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> menuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(menuBPClass.Class != nullptr)) return;

	menuClass = menuBPClass.Class;
}

void UPuzzleGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *menuClass->GetName());
}
void UPuzzleGameInstance::LoadMenu() {
	if (!ensure(menuClass != nullptr)) return;

	menu = CreateWidget<UMainMenu>(this, menuClass);
	if (!ensure(menu != nullptr)) return;

	menu->SetUp();

	menu->SetMenuInterface(this);
}
void UPuzzleGameInstance::Host() { //Host a Server
	if (menu != nullptr) {
		menu->TearDown();
	}

	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr))return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting")); //Used to show message on screen

	UWorld* world = GetWorld(); 
	if (!ensure(world != nullptr))return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"); //Travel to Level designed by Path in Content and ?listen is used to make the server listen for joins
}

void UPuzzleGameInstance::Join(const FString& adress) { //Join a server
	if (menu != nullptr) {
		menu->TearDown();
	}

	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr))return;

	engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *adress)); //Can add content %s only via a FString::Printf

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))return;

	playerController->ClientTravel(adress, ETravelType::TRAVEL_Absolute);
}