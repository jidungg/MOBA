// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "MOBAGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	currentPlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("currentPlayerCount : %d"), currentPlayerCount);
	if (currentPlayerCount >= 2)
	{
		GetWorldTimerManager().SetTimer(gameStartTimer,this,&ALobbyGameMode::StartGame,10);
	}

}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	currentPlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("currentPlayerCount : %d"), currentPlayerCount);
}

void ALobbyGameMode::StartGame()
{
	auto gameInstance = Cast<UMOBAGameInstance>(GetGameInstance());
	if (gameInstance == nullptr) return;

	gameInstance->StartSession();
	bUseSeamlessTravel = true;
	GetWorld()->ServerTravel("/Game/MOBA/Maps/Game?listen");
}
