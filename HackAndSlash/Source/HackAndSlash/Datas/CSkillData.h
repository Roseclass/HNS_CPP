#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/CStateComponent.h"
#include "CSkillData.generated.h"

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere)
		FName BoneName;
	UPROPERTY(EditAnywhere)
		float Lerp;
	UPROPERTY(EditAnywhere)
		float Power=0.0f;
	UPROPERTY(EditAnywhere)
		float Range = 0.0f;
	UPROPERTY(EditAnywhere)
		EWeaponState WeaponState;
	UPROPERTY(EditAnywhere)
		EPlayerState PlayerState;
	UPROPERTY(EditAnywhere)
		int32 SkillIndex;
	UPROPERTY(EditAnywhere)
		bool bCanMove;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* SkillImage;
	UPROPERTY(EditAnywhere)
		FText Name;
	UPROPERTY(EditAnywhere)
		FText Description;
};

UCLASS()
class HACKANDSLASH_API UCSkillData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FSkillInfo MontageData;
};