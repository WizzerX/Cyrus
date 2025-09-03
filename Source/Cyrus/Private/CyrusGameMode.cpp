// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusGameMode.h"
#include "NetworkingJson/JsonManager.h"

ACyrusGameMode::ACyrusGameMode()
{
	// stub
}

void ACyrusGameMode::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Error, TEXT("Begin Play is fired"));

	UJsonManager* Manager = NewObject<UJsonManager>();
	Manager->FetchJsonFromUrl(TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json"));

	


}
