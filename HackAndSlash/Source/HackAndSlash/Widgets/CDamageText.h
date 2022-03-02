#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDamageText.generated.h"

UCLASS()
class HACKANDSLASH_API ACDamageText : public AActor
{
	GENERATED_BODY()
	//property
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* Widget;
	float Damage;
protected:
public:

	//function
private:
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
		void PlayDamageText();
	UFUNCTION(BlueprintCallable)
		void Update(float InOpacity);
public:
	ACDamageText();
	void SetDamageText(float InDamage);

};
