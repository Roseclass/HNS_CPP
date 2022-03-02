#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TestComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class HACKANDSLASH_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

	//property
private:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* DeadMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* HittedMontage;
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		FString Type;
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCSkillComponent* Skill;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCEquimentComponent* Equipment;

	UPROPERTY(VisibleDefaultsOnly)
		class UTestComponent* Test;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane;//VirtualTexture(MINIMAP)
public:

	//function
private:

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
		void PlaySkill(int32 InIndex);
public:
	ACEnemy();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetRatioHP() { return Test->GetRatioHP(); }
	UFUNCTION(BlueprintPure)
		FORCEINLINE FString GetName() { return Name; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE FString GetType() { return Type; }
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RefreshHP(float InRatioHP,const FString& InName, const FString& InType);
};
