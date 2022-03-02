#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/CStateComponent.h"
#include "CWeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* DrawMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* SheathMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
		float Power = 0.0f;
	UPROPERTY(EditAnywhere)
		EWeaponState WeaponType;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACEquipment> EquimentClass;
};

UCLASS()
class HACKANDSLASH_API UCWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FWeaponInfo WeaponData;

	void BeginPlay(class ACharacter* InOwnerCharacter, class ACEquipment** OutAction);
};
