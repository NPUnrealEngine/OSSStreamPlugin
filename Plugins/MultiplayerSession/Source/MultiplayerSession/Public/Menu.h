// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UMultiplayerSessionSubsystem;
class UButton;
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();
	
protected:
	virtual bool Initialize() override;
	
	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> HostButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> JoinButton;

	/**
	 * A reference to multiplayer session subsystem
	 * 
	 * Note: this reference doesn't retain
	 */
	TWeakObjectPtr<UMultiplayerSessionSubsystem> MultiplayerSessionSubsystem;
};
