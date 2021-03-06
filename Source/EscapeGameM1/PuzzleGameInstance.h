// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAMEM1_API UPuzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& adress);
private:
	TSubclassOf<class UUserWidget> menuClass;
	class UMainMenu* menu;
};
