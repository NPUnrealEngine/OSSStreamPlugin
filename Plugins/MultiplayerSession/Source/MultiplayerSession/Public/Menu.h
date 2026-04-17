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
	void MenuSetup(int32 NumPublicConnections = 4, FString TypeOfMatch = FString(TEXT("tomneo2004_free_for_all")));

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();
	
	void MenuTeardown();
	
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
	
	int32 NumOfPublicConnections{4};
	FString MatchType{TEXT("tomneo2004_free_for_all")};
};
