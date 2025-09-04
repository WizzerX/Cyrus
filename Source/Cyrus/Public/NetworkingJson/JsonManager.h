
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "http.h"
#include "JsonManager.generated.h"

USTRUCT(BlueprintType)
struct  FBoxDataType
{
	GENERATED_BODY();


	UPROPERTY(BlueprintReadOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly) 
	FColor Color;
	UPROPERTY(BlueprintReadOnly)
	int32 Health = 0;
	UPROPERTY(BlueprintReadOnly) 
	int32 Score = 0;

};

USTRUCT(BlueprintType)
struct FBoxTransform
{

	GENERATED_BODY();


	UPROPERTY(BlueprintReadOnly)
	FString TypeName;
	
	UPROPERTY(BlueprintReadOnly)
	FVector Location;
	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;
	UPROPERTY(BlueprintReadOnly)
	FVector Scale;
	


};






UCLASS()
class CYRUS_API UJsonManager : public UObject
{
	GENERATED_BODY()
	
public:

	void FetchJsonFromUrl(const FString& URL);

	UJsonManager();

	bool ParseJSON(const FString& JsonString,TArray<FBoxDataType>& OutTypes,TArray<FBoxTransform>& OutObjects);

	UPROPERTY()
	TArray<FBoxDataType> BoxTypes;

	UPROPERTY()
	TArray<FBoxTransform> BoxObjects;

	UFUNCTION(BlueprintCallable, Category = "JSON")
	const TArray<FBoxDataType>& GetTypes() const { return BoxTypes; }

	UFUNCTION(BlueprintCallable, Category = "JSON")
	const TArray<FBoxTransform>& GetObjects() const { return BoxObjects; }


private:

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
