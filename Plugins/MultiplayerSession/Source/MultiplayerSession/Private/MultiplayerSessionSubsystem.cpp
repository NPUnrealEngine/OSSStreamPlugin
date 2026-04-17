// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

UMultiplayerSessionSubsystem::UMultiplayerSessionSubsystem()
{
	/* Bind delegate to callback functions */
	CreateSessionCompleteDelegate.BindUObject(this, &UMultiplayerSessionSubsystem::OnCreateSessionComplete);
	FindSessionsCompleteDelegate.BindUObject(this, &UMultiplayerSessionSubsystem::OnFindSessionsComplete);
	JoinSessionCompleteDelegate.BindUObject(this, &UMultiplayerSessionSubsystem::OnJoinSessionComplete);
	DestroySessionCompleteDelegate.BindUObject(this, &UMultiplayerSessionSubsystem::OnDestroySessionComplete);
	StartSessionCompleteDelegate.BindUObject(this, &UMultiplayerSessionSubsystem::OnStartSessionComplete);
}

void UMultiplayerSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMultiplayerSessionSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if (!SessionInterface.IsValid()) return;
	
	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}
	
	// Store delegate handle so it can be removed later
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	
	/* Setting session properties */
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = false;
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	/* Create session */
	ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		return;
	}
	
	if (GEngine)
	{
		FNamedOnlineSession* Session = SessionInterface->GetNamedSession(NAME_GameSession);
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Yellow,
			FString::Printf(TEXT("Steam session created: %s, MatchType: %s"), *Session->SessionName.ToString(), *MatchType)
		);
	}
}

void UMultiplayerSessionSubsystem::FindSession(int32 MaxSearchResults)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Yellow,
			FString(TEXT("Find game sessiones"))
		);
	}
}

void UMultiplayerSessionSubsystem::JoinSession(const FOnlineSessionSearchResult& SearchResult)
{
}

void UMultiplayerSessionSubsystem::DestroySession()
{
}

void UMultiplayerSessionSubsystem::StartSession()
{
}

void UMultiplayerSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerSessionSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void UMultiplayerSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UMultiplayerSessionSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerSessionSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
