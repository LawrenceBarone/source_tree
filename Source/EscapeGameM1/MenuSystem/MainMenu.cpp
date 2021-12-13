// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize() {
	bool succes = Super::Initialize();
	if (!succes)return false;

	if (!ensure(bHost != nullptr))return false;
	bHost->OnClicked.AddDynamic(this, &UMainMenu::HostSever);

	if (!ensure(bJoin != nullptr))return false;
	bJoin->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButtonJoinMenu != nullptr))return false;
	CancelButtonJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(CancelButtonJoinMenu != nullptr))return false;
	CancelButtonJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(ConfirmJoinMenu != nullptr))return false;
	ConfirmJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::JoinSever);

	return true;
}
void UMainMenu::SetMenuInterface(IMenuInterface* menuInt) {
	this->menuInterface = menuInt;
}
void UMainMenu::SetUp() {
	this->AddToViewport();

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))return;
	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;

	FInputModeUIOnly inputModeData;
	inputModeData.SetWidgetToFocus(this->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	playerController->SetInputMode(inputModeData);

	playerController->bShowMouseCursor = true;
}

void UMainMenu::TearDown() {
	this->RemoveFromViewport();
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))return;
	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;

	FInputModeGameOnly inputModeData;
	playerController->SetInputMode(inputModeData);
	playerController->bShowMouseCursor = false;
}

void UMainMenu::HostSever() {
	if (menuInterface != nullptr) {
		menuInterface->Host();
	}
}

void UMainMenu::JoinSever() {
	if (menuInterface != nullptr) {
		if (!ensure(IPAdressField != nullptr)) return;
		const FString& address = IPAdressField->GetText().ToString();
		menuInterface->Join(address);
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}