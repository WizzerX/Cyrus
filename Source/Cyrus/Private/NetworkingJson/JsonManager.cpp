// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkingJson/JsonManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Cube.h"

void UJsonManager::FetchJsonFromUrl(const FString& URL)
{
    FHttpModule& Http = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http.CreateRequest();

    Request->OnProcessRequestComplete().BindUObject(this, &UJsonManager::OnResponseReceived);
    Request->SetURL(URL);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();

    UE_LOG(LogTemp, Log, TEXT("Sending HTTP request to %s"), *URL);


}

UJsonManager::UJsonManager()
{



}

bool UJsonManager::ParseJSON(const FString& JsonString, TArray<FBoxDataType>& OutTypes, TArray<FBoxTransform>& OutObjects)
{
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    TSharedPtr<FJsonObject> Root;

    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON into object"));
        return false;
    }

    // ---- Parse "types" array ----
    const TArray<TSharedPtr<FJsonValue>>* TypesArr;
    if (Root->TryGetArrayField(TEXT("types"), TypesArr))
    {
        for (const TSharedPtr<FJsonValue>& Val : *TypesArr)
        {
            TSharedPtr<FJsonObject> Obj = Val->AsObject();
            if (!Obj.IsValid()) continue;

            FBoxDataType Type;
            Type.Name = Obj->GetStringField(TEXT("name"));
            Type.Health = Obj->GetIntegerField(TEXT("health"));
            Type.Score = Obj->GetIntegerField(TEXT("score"));
            


            // Parse color array [R,G,B]
            const TArray<TSharedPtr<FJsonValue>>* ColorArr;
            if (Obj->TryGetArrayField(TEXT("color"), ColorArr) && ColorArr->Num() == 3)
            {
                Type.Color = FColor(
                    (uint8)(*ColorArr)[0]->AsNumber(),
                    (uint8)(*ColorArr)[1]->AsNumber(),
                    (uint8)(*ColorArr)[2]->AsNumber()
                );
            }

            OutTypes.Add(Type);
        }
    }

    // ---- Parse "objects" array ----
    const TArray<TSharedPtr<FJsonValue>>* ObjectsArr;
    if (Root->TryGetArrayField(TEXT("objects"), ObjectsArr))
    {
        for (const TSharedPtr<FJsonValue>& Val : *ObjectsArr)
        {
            TSharedPtr<FJsonObject> Obj = Val->AsObject();
            if (!Obj.IsValid()) continue;

            FBoxTransform ObjData;
            ObjData.TypeName = Obj->GetStringField(TEXT("type"));

            // Transform object
            TSharedPtr<FJsonObject> TransformObj = Obj->GetObjectField(TEXT("transform"));
            auto GetVec = [&](const FString& Key) -> FVector
                {
                    const TArray<TSharedPtr<FJsonValue>>* Arr;
                    if (TransformObj->TryGetArrayField(Key, Arr) && Arr->Num() == 3)
                    {
                        return FVector(
                            (*Arr)[0]->AsNumber(),
                            (*Arr)[1]->AsNumber(),
                            (*Arr)[2]->AsNumber()
                        );
                    }
                    return FVector::ZeroVector;
                };

            ObjData.Location = GetVec(TEXT("location"));
            FVector Rot = GetVec(TEXT("rotation"));
            ObjData.Rotation = FRotator(Rot.X, Rot.Y, Rot.Z);
            ObjData.Scale = GetVec(TEXT("scale"));

            OutObjects.Add(ObjData);
        }
    }

    return true;

  
}

void UJsonManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP request failed"));
        return;
    }

    FString JsonString = Response->GetContentAsString();


    UE_LOG(LogTemp, Log, TEXT("Received JSON:\n%s"), *JsonString);

    // ?? Store the parsed results in the class properties
   BoxTypes.Empty();
    BoxObjects.Empty();

    if (ParseJSON(JsonString, BoxTypes, BoxObjects))
    {
        UE_LOG(LogTemp, Log, TEXT("Parsed %d types and %d objects"),    BoxTypes.Num(),BoxObjects.Num());

        if (BoxTypes.Num() > 0)
        {
            UE_LOG(LogTemp, Log, TEXT("First type: %s"), *BoxTypes[0].Name);
        }

        if (BoxObjects.Num() > 0)
        {
            UE_LOG(LogTemp, Log, TEXT("First object type: %s at location %s"),
                *BoxObjects[0].TypeName, *BoxObjects[0].Location.ToString());
        }

       
      
    }
    
}
