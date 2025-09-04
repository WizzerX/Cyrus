// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "NetworkingJson/JsonManager.h"
#include "iostream"
// Sets default values
ACube::ACube()
{
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	SetRootComponent(Cube);

    // Assign default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        Cube->SetStaticMesh(MeshAsset.Object);
    }
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/FirstPerson/m_Cube.m_Cube"));
    if (MaterialAsset.Succeeded())
    {
        Cube->SetMaterial(0, MaterialAsset.Object);
    }

    
	
}


void ACube::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Begin Play"));
	



}


void ACube::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

   


}

void ACube::InitFromType(const FBoxDataType& Data)
{
    Name = Data.Name;
    Health = Data.Health;
    Score = Data.Score;
    Color = Data.Color;

    // If you want to apply color to the mesh
    if (Cube && Cube->GetMaterial(0))
    {
        UE_LOG(LogTemp, Warning, TEXT("Material is Updated!"));
        UMaterialInstanceDynamic* DynMat = Cube->CreateAndSetMaterialInstanceDynamic(0);
        if (DynMat)
        {
            DynMat->SetVectorParameterValue("BaseColor", FLinearColor(Data.Color));
            UE_LOG(LogTemp, Warning, TEXT("Material is Updated!"));
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Initialized Cube %s with Health: %d, Score: %d"),
        *Name, Health, Score);



}






