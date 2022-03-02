#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_KMP.generated.h"


UCLASS()
class HACKANDSLASH_API UCWidget_KMP : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		bool Check(FString KMP , FString Str);

	UFUNCTION(BlueprintCallable)
		void MakeKMPArray(FString KMP);
private:
	TArray<int32> table;
};
