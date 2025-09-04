// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CubeWidget.h"
#include "Components/ProgressBar.h"

void UCubeWidget::SetHealth(float CurrnetHealth, float MaxHealth)
{
	if (HealthBar)
	{
		float Percent = CurrnetHealth / MaxHealth;
		HealthBar->SetPercent(FMath::Clamp(Percent, 0.0f, 1.0f));
		
	}


}
