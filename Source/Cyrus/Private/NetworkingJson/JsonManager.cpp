// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkingJson/JsonManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"


void UJsonManager::FetchJsonFromUrl(const FString& URL)
{
    FHttpModule& Http = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http.CreateRequest();

    Request->OnProcessRequestComplete().BindUObject(this, &UJsonManager::OnResponseRecived);
    Request->SetURL(URL);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();

    UE_LOG(LogTemp, Log, TEXT("Sending HTTP request to %s"), *URL);


}

UJsonManager::UJsonManager()
{



}

void UJsonManager::OnResponseRecived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP request failed"));
        return;
    }

    FString JsonString = Response->GetContentAsString();
    UE_LOG(LogTemp, Log, TEXT("Received JSON:\n%s"), *JsonString);




}
