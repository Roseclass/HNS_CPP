#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_VATS_Text.generated.h"

UCLASS()
class HACKANDSLASH_API UCWidget_VATS_Text : public UUserWidget
{
	GENERATED_BODY()
	//property
private:
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* PartMesh;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Rate;
public:

	//function
private:
protected:
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetPartMeshText(FName InMeshName);
	UFUNCTION(BlueprintImplementableEvent)
		void SetRateText(float InRate);
};
