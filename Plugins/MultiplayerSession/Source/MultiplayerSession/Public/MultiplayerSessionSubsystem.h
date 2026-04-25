// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSessionSubsystem.generated.h"

/* Custom delegates */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMultiplayerSessionSubsystem();
	
public: // Delegates
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * Create a steam game session for join
	 * @param NumPublicConnections number of player connections
	 * @param MatchType match type
	 */
	void CreateSession(int32 NumPublicConnections, FString MatchType);

	/**
	 * Find available steam game session for join
	 * @param MaxSearchResults max number for search result
	 */
	void FindSession(int32 MaxSearchResults = 10000);

	/**
	 * Join a steam game session
	 * @param SearchResult 
	 */
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	/**
	 * Destroy a steam game session
	 */
	void DestroySession();

	/**
	 * Start a steam game session
	 */
	void StartSession();
	
protected: // Callbacks for IOnlineSessionPtr
	/**
	 * Callback for creating a game session completed
	 * @param SessionName 
	 * @param bWasSuccessful 
	 */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	 * Callback for finding game sessions completed
	 * @param bWasSuccessful 
	 */
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	 * Callback for join a game session completed
	 * @param SessionName 
	 * @param Result 
	 */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/**
	 * Callback for destroy a game session completed
	 * @param SessionName 
	 * @param bWasSuccessful 
	 */
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	 * Callback for starting a game session completed
	 * @param SessionName 
	 * @param bWasSuccessful 
	 */
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
private:
	/**
	 * The session interface instance
	 */
	IOnlineSessionPtr SessionInterface;

	/**
	 * Delegate for creating a session completed
	 */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	/**
	 * Delegate handle for creating a session 
	 */
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	
	/**
	 * Delegate for finding sessions completed
	 */
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	
	/**
	 * Delegate handle for finding sessions
	 */
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	
	/**
	 * Delegate for joining a session completed
	 */
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	
	/**
	 * Delegate handle for joining a session
	 */
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
	/**
	 * Delegate for destroy a session completed
	 */
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	
	/**
	 * Delegate handle for destroy a session
	 */
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	
	/**
	 * Delegate for starting a session completed
	 */
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	
	/**
	 * Delegate handle for starting a session
	 */
	FDelegateHandle StartSessionCompleteDelegateHandle;
};
