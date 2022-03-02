#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVATS_Text_Actor.generated.h"

UCLASS()
class HACKANDSLASH_API ACVATS_Text_Actor : public AActor
{
	GENERATED_BODY()	
	//property
private:
	class UCWidget_VATS_Text* Child;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UWidgetComponent* Widget;
public:

	//function
private:
protected:
	virtual void BeginPlay() override;
public:
	ACVATS_Text_Actor();
	void SetText(FName InMeshName, float InRate);
};
