// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			//들어온 총 인원 
			//첫인자 1이면 디버그메시지가 쌓이지않고 새롭게 들어올떄마다 새로운 플레이어로 갱신되서 들어왔다고 알림
			GEngine->AddOnScreenDebugMessage(
				1,
				600.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game : %d"), NumberOfPlayers)
			);

			//현재 들어온사람 이름 출력
			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();
				
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
			
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players in game : %d"), NumberOfPlayers - 1)
		);


		FString PlayerName = PlayerState->GetPlayerName();

		GEngine->AddOnScreenDebugMessage(
			-1,
			60.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has exited the game!"), *PlayerName)
		);
	}
}
