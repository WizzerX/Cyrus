// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "NetworkingJson/JsonManager.h"
#include "iostream"
#include "Components/WidgetComponent.h"
#include "Widget/CubeWidget.h"
#include "Components/Widget.h"


// Sets default values
ACube::ACube()
{
	PrimaryActorTick.bCanEverTick = true;


    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
    SetRootComponent(Cube);

    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    Root->SetupAttachment(RootComponent);
    // Assign default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        Cube->SetStaticMesh(MeshAsset.Object);
    }
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/_Game/Material/m_Cube.m_Cube"));
    if (MaterialAsset.Succeeded())
    {
        Cube->SetMaterial(0, MaterialAsset.Object);
    }

   
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    WidgetComponent->SetupAttachment(Root);
   
    // Force HUD-like behavior
    WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    WidgetComponent->SetDrawSize(FVector2D(200, 20));   // fixed pixel size
    WidgetComponent->SetRelativeLocation(FVector(0, 0, 100)); // float above cube
    WidgetComponent->SetRelativeScale3D(FVector(1.0f)); //
    
 



}


void ACube::TakeDamage()
{
    Health -= 1;


    UpdateHealthWidget();

    if (Health <= 0.0f)
    {
        this->Destroy();
    }





}

void ACube::BeginPlay()
{
	Super::BeginPlay();
	
    UpdateHealthWidget();
   


}


void ACube::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

    if (WidgetComponent && GetWorld())
    {
        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            if (PC->PlayerCameraManager)
            {
                FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
                FVector WidgetLocation = WidgetComponent->GetComponentLocation();

                FVector ToCamera = CameraLocation - WidgetLocation;
                ToCamera.Z = 0; // Optional: keep it upright (no tilt)

                FRotator LookAtRotation = FRotationMatrix::MakeFromX(ToCamera).Rotator();
                WidgetComponent->SetWorldRotation(LookAtRotation);
            }
        }
    }


}

void ACube::InitFromType(const FBoxDataType& Data)
{
    Name = Data.Name;
    Health = Data.Health;
    Score = Data.Score;
    Color = Data.Color;
    MaxHealth = Data.Health;
    UpdateHealthWidget();

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

    


}

void ACube::UpdateHealthWidget()
{
      if (UCubeWidget* Widget = Cast<UCubeWidget>(WidgetComponent->GetUserWidgetObject()))
      { 
          Widget->SetHealth(Health, MaxHealth);
         
          
          UE_LOG(LogTemp, Error, TEXT("Progress Bar Called!"));
      } 
}








