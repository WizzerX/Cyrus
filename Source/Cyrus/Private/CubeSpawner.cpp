// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSpawner.h"
#include "NetworkingJson/JsonManager.h"
#include "Cube.h"

// Sets default values
ACubeSpawner::ACubeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<ACube> CubeBPClass(
   TEXT("/Game/_Game/Blueprints/Item/goodBox.good.Box"));

    if (CubeBPClass.Succeeded())
    {
        CubeBlueprintClass = CubeBPClass.Class;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find BP_Cube! Check the path."));
    }
  



}


// Called when the game starts or when spawned
void ACubeSpawner::BeginPlay()
{
	Super::BeginPlay();
  
	JsonManager = NewObject<UJsonManager>(this);
	if (JsonManager)
	{
		JsonManager->FetchJsonFromUrl(TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json"));
	}



}

// Called every frame
void ACubeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    if (JsonManager && !bHasSpawned && JsonManager->GetObjects().Num() > 0)
    {
        for (const FBoxTransform& Obj : JsonManager->GetObjects())
        {
            const FBoxDataType* FoundType = JsonManager->GetTypes().FindByPredicate(
                [&](const FBoxDataType& T) { return T.Name == Obj.TypeName; }
            );

            if (FoundType)
            {
                
               

                ACube* NewCube = GetWorld()->SpawnActor<ACube>(
                    CubeBlueprintClass,
                    Obj.Location,
                    Obj.Rotation
                );
                    

             

                if (NewCube)
                {
                    NewCube->SetActorScale3D(Obj.Scale);
                    NewCube->InitFromType(*FoundType);
                    // add InitFromType later
                    NewCube->Name = FoundType->Name;
                    NewCube->Health = FoundType->Health;
                    NewCube->Score = FoundType->Score;
                    NewCube->Color = FoundType->Color;

                   
                }
            }
        }

        bHasSpawned = true; 
    }



}

