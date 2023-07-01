// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterGameMode.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* EliminatedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	if (EliminatedCharacter)
	{
		EliminatedCharacter->Elim();
	}
}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	// Check to see if the character is valid to be destroyed
	if (ElimmedCharacter)
	{
		// This is a inherited function from Pawn that helps unposses the character they were using.
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}

	// Check to see if controller is still playing
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		// We want them to respawn at random places of the map
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1); // We want to have -1 to have the accurate number, if we don't we will crash with this math.

		//Check to see where are all the players with some math and then put them where the players are further than the respawn point
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}
