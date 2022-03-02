#pragma once

#include "CoreMinimal.h"
#include "Characters/CPlayer.h"
#include "CRevenant.generated.h"

UCLASS()
class HACKANDSLASH_API ACRevenant : public ACPlayer
{
	GENERATED_BODY()
	//property
private:
	UPROPERTY(EditAnywhere)
		class UMaterialInstance* GlowWeaponMaterial[2];
	UPROPERTY(EditAnywhere)
		int32 GlowMaterialNumber;
protected:
public:

	//function
private:
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void HideWeapon() override;
	virtual void RevealWeapon() override;
	UFUNCTION(BlueprintCallable)
		void StartVATS();
	UFUNCTION(BlueprintCallable)
		void UpdateVATS(float InTimeRatio);
	UFUNCTION(BlueprintCallable)
		void FinishVATS();
public:
	ACRevenant();
};