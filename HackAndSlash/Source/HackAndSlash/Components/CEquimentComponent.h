#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquimentComponent.generated.h"

UCLASS()
class HACKANDSLASH_API UCEquimentComponent : public UActorComponent
{
	GENERATED_BODY()
		//property
private:
	UPROPERTY(EditAnywhere)
		TArray<class UCWeaponData*> EquipmentDatas;
	UPROPERTY(EditAnywhere)
		class UCWeaponData* OriginalData;

	UPROPERTY()
		TArray<class ACEquipment*> Datas;
	UPROPERTY(EditAnywhere)
		int32 WeaponIndex = 0;

	float Power;
protected:
public:

	//function
private:	
protected:
	virtual void BeginPlay() override;
public:
	UCEquimentComponent();

	UFUNCTION()//Player.cpp->BeginPlay
		void ChangeToOriginal();
	UFUNCTION()//Player.cpp->BeginPlay
		void ChangeToEquiment();

	FORCEINLINE float GetWeaponPower() { return Power; }
	void OnCollision();
	void OffCollision();
	void ResetTarget();
};
