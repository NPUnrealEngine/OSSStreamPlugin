// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionSubsystem.h"

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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Yellow,
			FString(TEXT("Create game session"))
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
