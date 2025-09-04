// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CubeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYRUS_API UCubeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float CurrnetHealth, float MaxHealth);

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UProgressBar* HealthBar;







	
};
