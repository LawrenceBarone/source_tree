// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAMEM1_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* menuInterface);

	void SetUp();
	void TearDown();
	
protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* bHost;

	UPROPERTY(meta = (BindWidget))
	class UButton* bJoin;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButtonJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAdressField;
	
	UFUNCTION()
	void HostSever();

	UFUNCTION()
	void JoinSever();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();
	
	IMenuInterface* menuInterface;
};
