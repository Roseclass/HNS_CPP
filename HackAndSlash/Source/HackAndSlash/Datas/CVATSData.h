#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CVATSData.generated.h"

UCLASS()
class HACKANDSLASH_API UCVATSData : public UDataAsset
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere)
		TArray<FName> Parent;
	UPROPERTY(EditAnywhere)
		TMap<FName, FName> UIPartName;
	UPROPERTY(EditAnywhere)
		TMap<FName, float> UIPartRate;
	UPROPERTY(EditAnywhere)
		TMap<FName,class USkeletalMesh*> Part;
	UPROPERTY(EditAnywhere)
		TMap<FName, class USkeletalMesh*> Origin;
};
