
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "http.h"
#include "JsonManager.generated.h"

UCLASS()
class CYRUS_API UJsonManager : public UObject
{
	GENERATED_BODY()
	
public:

	void FetchJsonFromUrl(const FString& URL);

	UJsonManager();

private:

	void OnResponseRecived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
