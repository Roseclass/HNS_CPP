#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVATS_Info_Actor.generated.h"

UCLASS()
class HACKANDSLASH_API ACVATS_Info_Actor : public AActor
{
	GENERATED_BODY()
	//property
private:
	class ACPlayerController* Player;
	class UCWidget_VATS_Info* Child;
	float ScreenOffset = 300.0f;
	float Yaw = 0.0f;
	float Pitch = 0.0f;
	float Roll = 90.0f;
	FVector Offset = FVector(0.0f, 0.0f, -50.0f);
	FVector Scale = FVector(0.3f, 0.3f, 0.3f);
	FVector2D ViewportSize;
protected:	
public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UWidgetComponent* Widget;
	//function
private:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	ACVATS_Info_Actor();
	UFUNCTION(BlueprintCallable)
		void SetBulletCount(int32 InCount);
	UFUNCTION(BlueprintCallable)
		void IncreaseBulletCount();
	UFUNCTION(BlueprintCallable)
		void DecreaseBulletCount();
	UFUNCTION(BlueprintCallable)
		void SetViewportSize(FVector2D InSize);
};
