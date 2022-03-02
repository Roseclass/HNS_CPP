#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Damage.generated.h"

UCLASS()
class HACKANDSLASH_API UCWidget_Damage : public UUserWidget
{
	GENERATED_BODY()
	//property
private:
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* DamageText;
public:

	//function
private:
protected:
public:
	void SetDamageText(float InDamage);
};
