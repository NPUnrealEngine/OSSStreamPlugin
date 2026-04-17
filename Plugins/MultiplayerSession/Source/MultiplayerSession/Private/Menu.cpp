// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "MultiplayerSessionSubsystem.h"
#include "Components/Button.h"

void UMenu::MenuSetup(int32 NumPublicConnections, FString TypeOfMatch)
{
	NumOfPublicConnections = NumPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);
	
	// Setup input mode and mouse cursor
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(true);
		}
	}
	
	// Get UMultiplayerSessionSubsystem instance
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}
	
	if (MultiplayerSessionSubsystem.IsValid())
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(
			this, 
			&ThisClass::OnCreateSession
		);
	}
}

void UMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}
}

void UMenu::NativeDestruct()
{
	MenuTeardown();
	
	Super::NativeDestruct();
}

void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionSubsystem.IsValid())
	{
		MultiplayerSessionSubsystem->CreateSession(NumOfPublicConnections, MatchType);
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Yellow,
			FString(TEXT("Join button clicked"))
		);
	}
	
	if (MultiplayerSessionSubsystem.IsValid())
	{
		MultiplayerSessionSubsystem->FindSession();
	}
}

void UMenu::MenuTeardown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			FInputModeGameOnly InputModeData;
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(false);
		}
	}
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Create session fail"))
			);
		}
		
		return;
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Yellow,
			FString(TEXT("Create session Success"))
		);
	}
	if (UWorld* World = GetWorld())
	{
		World->ServerTravel("/Game/ThirdPerson/Lobby?listen");
	}
}
