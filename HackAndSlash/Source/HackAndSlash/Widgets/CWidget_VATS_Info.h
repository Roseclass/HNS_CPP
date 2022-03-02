#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_VATS_Info.generated.h"

UCLASS()
class HACKANDSLASH_API UCWidget_VATS_Info : public UUserWidget
{
	GENERATED_BODY()
	//property
private:
	int32 BulletCount=5;
	int32 MaxCount=5;	
protected:	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<class UImage*> BulletImages;
	//function
private:
protected:
public:
	UFUNCTION(BlueprintCallable)
		void BeginPlay();
	UFUNCTION(BlueprintCallable)
		void SetBulletCount(int32 InCount);
	UFUNCTION(BlueprintCallable)
		void IncreaseBulletCount();
	UFUNCTION(BlueprintCallable)
		void DecreaseBulletCount();
};
